/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:40:02 by lcocozza          #+#    #+#             */
/*   Updated: 2023/07/13 16:19:51 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

static int	__init_game(t_config config, t_game *game)
{
	game->config.teams = config.teams;
	game->config.players = config.teams * config.players;
	game->board.height = config.board_height;
	game->board.width = config.board_width;
	game->board.areas = NULL;
	game->board.areas_len = 0;
	game->players = NULL;
	game->teams = init_teams(config.teams);
	if (game->teams == NULL)
		return (-1);
	return (0);
}

int	master_process(t_config config, t_game *game)
{
	if (__init_game(config, game) == -1)
		return (EXIT_ERROR);

	game->board.areas_len = divide_board_equal_area(
		&game->board.areas,
		config.board_width,
		config.board_height,
		config.teams
	);
	game->players = spread_players(game);
	if (game->players == NULL)
		return (EXIT_ERROR);
	print_board(game);
	return (EXIT_SUCCESS);
}
