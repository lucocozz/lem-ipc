/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:50:01 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/25 19:00:45 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"


static void	__waiting_setup(t_game *game, int uid)
{
	printf("Player %d is waiting for setup\n", uid);
	while (game->status == Setuping)
		msleep(1);
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

		is_dead = death_check(config, game, teams, players, uid);
		if (is_dead == 1) {
			sem_post(sem);
			continue ;
		} else if (is_dead == 2) {
			sem_post(sem);
			break ;
		}

		t_player *enemy = get_enemy(config, players, uid, &locked_enemy, channel_id);
		if (enemy == NULL) {
			sem_post(sem);
			continue ;
		}

		if (move_to_enemy(config, players, &players[uid], *enemy) == 0) {
			is_stuck++;
			if (is_stuck == MAX_TURN_STUCK) {
				t_player *ally = find_nearest_ally_to_enemy(config, players, uid, *enemy);
				if (ally != NULL)
					request_assist(channel_id, *ally, *enemy);
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
