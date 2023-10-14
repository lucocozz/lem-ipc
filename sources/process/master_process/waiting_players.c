/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_players.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:59:01 by lcocozza          #+#    #+#             */
/*   Updated: 2023/10/14 20:17:36 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

void	waiting_players(t_process process, sem_t *sem, t_config *config, t_game *game)
{
	while (game->players_len < config->len.total_players)
	{
		sem_wait(sem);
		game->players = shmat(process.shm.players.id, NULL, 0);
		system("clear");
		printf("Waiting for players...\n");
		printf("Players: %d/%d\n", game->players_len, config->len.total_players);
		print_board(config, game);
		sem_post(sem);
		usleep(50000);
	}
}
