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

t_player	*spread_players(t_polygon *areas, int areas_len)
{
	t_player	*players;

	players = malloc(sizeof(t_player) * PLAYERS_NUM);
	if (players == NULL)
		return (NULL);

	for (int i = 0; i < PLAYERS_NUM; ++i)
	{
		t_point	point;

        point.x = BOARD_WIDTH * halton_sequence(i, 2) + 1;
        point.y = BOARD_HEIGHT * halton_sequence(i, 3) + 1;

		players[i].position = point;
		players[i].team = TEAMS[area_id_is(areas, areas_len, point)];
		players[i].status = Alive;
    }

	return (players);
}
