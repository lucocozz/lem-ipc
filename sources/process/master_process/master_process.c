/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:40:02 by lcocozza          #+#    #+#             */
/*   Updated: 2023/08/01 11:38:25 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

static void	__init_game(t_config *config, t_player *players, t_game *game)
{
	game->players = players;
	game->players_len = 0;
	game->teams = init_teams(config->len.teams);
}

int	master_process(t_config *config, t_player *players, t_game *game)
{
	t_polygon	*areas = NULL;
	int 		areas_len = 0;

	__init_game(config, players, game);
	if (game->teams == NULL)
		return (EXIT_ERROR);
	areas_len = divide_board_equal_area(
		&areas,
		config->board.width,
		config->board.height,
		config->len.teams
	);
	spread_players(config, game, areas, areas_len);
	free_polygons(areas, areas_len);
	sem_unlink(SEM_NAME);
	waiting_players(config, game);
	return (EXIT_SUCCESS);
}
