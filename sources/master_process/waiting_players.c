/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_players.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:59:01 by lcocozza          #+#    #+#             */
/*   Updated: 2023/07/17 14:59:21 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

void	waiting_players(t_game *game)
{
	while (game->players_len < game->config.players)
	{
		system("clear");
		printf("Waiting for players...\n");
		printf("Players: %d/%d\n", game->players_len, game->config.players);
		print_board(game);
		usleep(50000);
	}
}
