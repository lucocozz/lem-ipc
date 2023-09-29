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

static bool	__check_is_full(t_config *config, int teams[])
{
	for (int i = 0; i < config->len.teams; ++i) {
		if (teams[i] < config->len.players)
			return (false);
	}
	return (true);
}

static bool	__add_in_team(t_config *config, t_game *game, t_point point, t_polygon *areas, int areas_len)
{
	static int	index = 0;
	static int	teams[MAX_TEAMS] = {0};
	int			area_id = area_id_is(areas, areas_len, point);

	if (teams[area_id] < config->len.players)
	{
		game->players[index].position = point;
		game->players[index].team = game->teams[area_id];
		game->players[index].status = Waiting;
		
		teams[area_id]++;
		index++;

		return (__check_is_full(config, teams));
	}
	return (false);
}

void	spread_players(t_config *config, t_game *game, t_polygon *areas, int areas_len)
{
	bool		is_full = false;

	for (int i = rand_range(0, 100); is_full == false; ++i)
	{
		t_point	point;

        point.x = config->board.width * halton_sequence(i, 2);
        point.y = config->board.height * halton_sequence(i, 3);

		if (point.x < config->board.width && point.y < config->board.height)
			is_full = __add_in_team(config, game, point, areas, areas_len);
    }
}
