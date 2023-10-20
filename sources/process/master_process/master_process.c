/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:40:02 by lcocozza          #+#    #+#             */
/*   Updated: 2023/10/20 15:44:36 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

static void	__init_game(t_config *config, t_game *game, t_team *teams)
{
	game->status = Setuping;
	game->teams_alive = config->len.teams;
	game->players_len = 0;
	init_teams(teams, config->len.teams, config->len.players);
}

char	*__get_title()
{
	char	*title_path[] = {
		"titles/tmplr.txt", "titles/crawford2.txt", "titles/fire.txt", "titles/graceful.txt",
		"titles/grafitti.txt", "titles/modular.txt", "titles/slant.txt", "titles/stop.txt",
		"titles/big.txt"
	};
	int title_id = rand_range(0, LEN(title_path) - 1);
	return (read_file(title_path[title_id]));
}

int	master_process(t_config *config, t_game *game, t_team *teams, t_player *players)
{
	t_polygon	*areas = NULL;
	int 		areas_len = 0;
	char		*title = __get_title();

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	__init_game(config, game, teams);
	areas_len = divide_board_equal_area(
		&areas,
		config->board.width,
		config->board.height,
		config->len.teams
	);
	spread_players(config, teams, players, areas, areas_len);
	free_polygons(areas, areas_len);
	sem_unlink(SEM_NAME);
	waiting_players(config, game, players, title);
	game_loop(config, game, players, title);
	free(title);
	return (EXIT_SUCCESS);
}
