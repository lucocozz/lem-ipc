/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:09:47 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/20 19:21:11 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

void	game_loop(t_config *config, t_game *game, t_player *players, char *title)
{
	game->status = Running;
	while (game->teams_alive > 1 && game->players_len > 2 && g_sig == 0)
	{
		system("clear");
		if (title != NULL)
			printf("%s%s%s\n", TEXT_BOLD, title, TEXT_RESET);
		print_board(config, players);
		msleep(REFRESH_DELAY);
	}
	game->status = Finished;
}
