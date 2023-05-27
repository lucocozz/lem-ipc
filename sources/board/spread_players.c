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

static bool	__check_is_full(int teams[])
{
	for (int i = 0; i < (int)TEAMS_LEN; ++i) {
		if (teams[i] < TEAM_SIZE)
			return (false);
	}
	return (true);
}

static bool	__add_in_team(t_player *players, t_point point, t_polygon *areas, int areas_len)
{
	static int	index = 0;
	static int	teams[TEAMS_LEN] = {0};
	int			area_id = area_id_is(areas, areas_len, point);

	if (teams[area_id] < TEAM_SIZE)
	{
		players[index].position = point;
		players[index].team = TEAMS[area_id];
		players[index].status = Alive;
		
		teams[area_id]++;
		index++;

		return (__check_is_full(teams));
	}
	return (false);
}

t_player	*spread_players(t_polygon *areas, int areas_len)
{
	t_player	*players;
	bool		is_full = false;

	players = malloc(sizeof(t_player) * PLAYERS_NUM);
	if (players == NULL)
		return (NULL);

	for (int i = 1; is_full == false; ++i)
	{
		t_point	point;

        point.x = BOARD_WIDTH * halton_sequence(i, 2);
        point.y = BOARD_HEIGHT * halton_sequence(i, 3);

		if (point.x < BOARD_WIDTH && point.y < BOARD_HEIGHT)
			is_full = __add_in_team(players, point, areas, areas_len);
    }

	return (players);
}
