/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_players.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:59:01 by lcocozza          #+#    #+#             */
/*   Updated: 2023/10/20 19:20:54 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

void	waiting_players(t_config *config, t_game *game, t_player *players, char *title)
{
	while (game->players_len < config->len.total_players && g_sig == 0)
	{
		system("clear");
		if (title != NULL)
			printf("%s%s%s\n", TEXT_BOLD, title, TEXT_RESET);
		printf("Waiting for players...\n");
		printf("Players: %d/%d\n", game->players_len, config->len.total_players);
		print_board(config, players);
		msleep(REFRESH_DELAY);
	}
	if (g_sig != 0)
		game->status = Finished;
}
