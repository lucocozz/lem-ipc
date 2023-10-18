/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:40:02 by lcocozza          #+#    #+#             */
/*   Updated: 2023/10/18 18:42:31 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

static void	__init_game(t_config *config, t_game *game)
{
	game->status = Setuping;
	game->teams_alive = config->len.teams;
	game->players_len = 0;
	game->teams = init_teams(config->len.teams, config->len.players);
}

int	master_process(t_process process, t_config *config, t_player *players, t_game *game)
{
	t_polygon	*areas = NULL;
	int 		areas_len = 0;
	sem_t 		*semaphore = sem_open(SEM_NAME, O_CREAT, PERMS, 1);

	__init_game(config, game);
	if (game->teams == NULL)
		return (EXIT_ERROR);
	areas_len = divide_board_equal_area(
		&areas,
		config->board.width,
		config->board.height,
		config->len.teams
	);
	spread_players(config, game, players, areas, areas_len);
	free_polygons(areas, areas_len);
	waiting_players(config, game, players);
	game_loop(config, game, players);
	sem_close(semaphore);
	sem_unlink(SEM_NAME);
	//! n'oublie pas d'enlever cette ligne
	(void)process;
	return (EXIT_SUCCESS);
}
