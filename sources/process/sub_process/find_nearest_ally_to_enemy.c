/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_nearest_ally_to_enemy.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:29:55 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/25 15:49:23 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

t_player	*find_nearest_ally_to_enemy(t_config *config, t_player *players, int uid, t_player enemy)
{
	int distance = 0;
	int nearest_ally_id = -1;
	int	team_id = players[uid].team.id;

	for (int i = 0; i < config->len.total_players; ++i)
	{
		if (players[i].team.id == team_id && players[i].status == Alive && i != uid)
		{
			int enemy_distance = manhattan_distance(players[i].position, enemy.position);
			int ally_distance = manhattan_distance(players[uid].position, players[i].position);
			int new_distance = enemy_distance + ally_distance;
			if (new_distance < distance || distance == 0) {
				nearest_ally_id = i;
				distance = new_distance;
			}
		}
	}
	if (nearest_ally_id == -1)
		return (NULL);
	return (&players[nearest_ally_id]);
}
