/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:26:14 by lcocozza          #+#    #+#             */
/*   Updated: 2023/10/25 15:56:15 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

static int	__init_player(sem_t *sem, t_game *game, t_player *players)
{
	t_player	*player = &players[game->players_len];

	sem_wait(sem);
	player->pid = getpid();
	player->status = Alive;
	player->uid = game->players_len;
	game->players_len++;
	sem_post(sem);
	printf("Player %d joining team %d\n", player->uid, player->team.id);
	return (player->uid);
}

void	sub_process(t_config *config, t_game *game, t_team *teams, t_player *players)
{
	sem_t *semaphore = sem_open(SEM_NAME, O_CREAT, SHM_PERMS, 1);

	int uid = __init_player(semaphore, game, players);
	player_loop(config, game, teams, players, semaphore, uid);
	sem_close(semaphore);
	sem_unlink(SEM_NAME);
}
