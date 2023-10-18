/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:40:02 by lcocozza          #+#    #+#             */
/*   Updated: 2023/10/18 19:59:53 by lucocozz         ###   ########.fr       */
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

int	master_process(t_config *config, t_game *game, t_team *teams, t_player *players)
{
	t_polygon	*areas = NULL;
	int 		areas_len = 0;

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
	waiting_players(config, game, players);
	game_loop(config, game, players);
	return (EXIT_SUCCESS);
}
