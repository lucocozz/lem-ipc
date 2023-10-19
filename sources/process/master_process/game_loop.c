/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:09:47 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/19 21:08:51 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

char	*__get_title()
{
	char	*title_path[] = {
		"titles/big.txt", "titles/crawford2.txt", "titles/fire.txt", "titles/graceful.txt",
		"titles/grafitti.txt", "titles/modular.txt", "titles/slant.txt", "titles/stop.txt",
		"titles/tmplr.txt"
	};
	int title_id = rand_range(0, LEN(title_path) - 1);
	return (read_file(title_path[title_id]));
}


void	game_loop(t_config *config, t_game *game, t_player *players)
{
	char	*title = __get_title();
	game->status = Running;
	while (game->teams_alive > 1 && game->players_len > 2)
	{
		system("clear");
		if (title != NULL)
			printf("%s\n", title);
		print_board(config, players);
		msleep(REFRESH_DELAY);
	}
	game->status = Finished;
}
