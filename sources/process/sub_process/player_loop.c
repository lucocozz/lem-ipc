/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:50:01 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/25 18:39:37 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"


static void	__waiting_setup(t_game *game, int uid)
{
	printf("Player %d is waiting for setup\n", uid);
	while (game->status == Setuping)
		msleep(1);
}

static t_player	*__get_enemy(t_config *config, t_player *players, int uid,
	t_player **locked_enemy, int channel_id)
{
	t_msgbuff	msg = {0};

	errno = 0;
	if (msgrcv(channel_id, &msg, sizeof(msg.data), Assist, IPC_NOWAIT | MSG_NOERROR) != -1) {
		if (msg.data[Ally] == (int8_t)uid) {
			*locked_enemy = &players[msg.data[Enemy]];
			printf("%sTaking assist request%s\n", TEXT_GREEN, TEXT_RESET);
		}
		else
			msgsnd(channel_id, &msg, sizeof(t_msgbuff), 0);
	}

	if (*locked_enemy != NULL && (*locked_enemy)->status == Alive)
		return (*locked_enemy);
	*locked_enemy = NULL;
	return (find_nearest_enemy(config, players, uid));
}

static void	__request_assist(int channel_id, t_player ally, t_player enemy)
{
	t_msgbuff	msg = {0};

	errno = 0;
	msg.type = Assist;
	msg.data[Ally] = ally.uid;
	msg.data[Enemy] = enemy.uid;
	msgsnd(channel_id, &msg, sizeof(t_msgbuff), 0);
	printf("%sAssist requested%s\n", TEXT_ORANGE, TEXT_RESET);
}

void	player_loop(t_config *config, t_game *game, t_team *teams,
	t_player *players, sem_t *sem, int uid)
{
	int			is_dead = 0;
	int			is_stuck = 0;
	t_player	*locked_enemy = NULL;
	int			team_id = players[uid].team.id;
	int 		channel_id = msgget(MSGQ_BASE_KEY + team_id, IPC_CREAT | MSG_PERMS);

	__waiting_setup(game, uid);
	printf("Player %d is running\n", uid);
	while (game->status == Running)
	{
		sem_wait(sem);

		//! if signal is received, kill player
		is_dead = death_check(config, game, teams, players, uid);
		if (is_dead == 1) {
			sem_post(sem);
			continue ;
		} else if (is_dead == 2) {
			sem_post(sem);
			break ;
		}

		t_player *enemy = __get_enemy(config, players, uid, &locked_enemy, channel_id);
		if (enemy == NULL) {
			sem_post(sem);
			continue ;
		}

		if (move_to_enemy(config, players, &players[uid], *enemy) == 0) {
			is_stuck++;
			if (is_stuck == MAX_TURN_STUCK) {
				t_player *ally = find_nearest_ally_to_enemy(config, players, uid, *enemy);
				if (ally != NULL)
					__request_assist(channel_id, *ally, *enemy);
			}
			sem_post(sem);
			continue ;
		} else
			is_stuck = 0;

		msleep(MOVE_DELAY);
		sem_post(sem);
		if (config->one_move == true)
			msleep(1);
		else usleep(50);
	}
}
