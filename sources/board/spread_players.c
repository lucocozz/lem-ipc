/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spread_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:58:51 by lcocozza          #+#    #+#             */
/*   Updated: 2023/05/25 13:44:57 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

static bool	__check_is_full(t_game *game, int teams[])
{
	for (int i = 0; i < game->config.teams; ++i) {
		if (teams[i] < game->config.players / game->config.teams)
			return (false);
	}
	return (true);
}

static bool	__add_in_team(t_game *game, t_player *players, t_point point)
{
	static int	index = 0;
	static int	teams[MAX_TEAMS] = {0};
	int			area_id = area_id_is(game->board.areas, game->board.areas_len, point);

	if (teams[area_id] < game->config.players / game->config.teams)
	{
		players[index].position = point;
		players[index].team = game->teams[area_id];
		players[index].status = Alive;
		
		teams[area_id]++;
		index++;

		return (__check_is_full(game, teams));
	}
	return (false);
}

t_player	*spread_players(t_game *game)
{
	t_player	*players;
	bool		is_full = false;

	players = malloc(sizeof(t_player) * game->config.players);
	if (players == NULL)
		return (NULL);

	for (int i = rand_range(0, 100); is_full == false; ++i)
	{
		t_point	point;

        point.x = game->board.width * halton_sequence(i, 2);
        point.y = game->board.height * halton_sequence(i, 3);

		if (point.x < game->board.width && point.y < game->board.height)
			is_full = __add_in_team(game, players, point);
    }

	return (players);
}
