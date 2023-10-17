/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_players.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:59:01 by lcocozza          #+#    #+#             */
/*   Updated: 2023/10/17 17:01:31 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

void	waiting_players(t_config *config, t_game *game, t_player *players)
{
	while (game->players_len < config->len.total_players)
	{
		system("clear");
		printf("Waiting for players...\n");
		printf("Players: %d/%d\n", game->players_len, config->len.total_players);
		print_board(config, players);
		msleep(50);
	}
	system("clear");
}
