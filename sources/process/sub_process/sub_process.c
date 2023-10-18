/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:26:14 by lcocozza          #+#    #+#             */
/*   Updated: 2023/10/18 18:41:43 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

static int	__init_player(sem_t *sem, t_game *game, t_player *players)
{
	printf("Waiting for player %d\n", game->players_len);
	sem_wait(sem);
	players[game->players_len].pid = getpid();
	players[game->players_len].status = Alive;
	game->players_len++;
	sem_post(sem);
	printf("Player %d is ready\n", game->players_len - 1);
	return (game->players_len - 1);
}

void	sub_process(t_config *config, t_player *players, t_game *game)
{
	sem_t *semaphore = sem_open(SEM_NAME, O_CREAT, PERMS, 1);

	int id = __init_player(semaphore, game, players);
	player_loop(config, game, players, semaphore, id);
	sem_close(semaphore);
	sem_unlink(SEM_NAME);
}
