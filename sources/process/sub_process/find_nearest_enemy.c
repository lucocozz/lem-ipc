/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_nearest_enemy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 20:44:54 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/18 20:45:12 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

int __calculate_distance(t_player player, t_player enemy) {
	return abs(enemy.position.x - player.position.x) + abs(enemy.position.y - player.position.y);
}

//? are based on the principle that an enemy can always be found.
t_player	*find_nearest_enemy(t_config *config, t_player *players, int id)
{
	int distance = 0;
	int nearest_enemy_id = -1;

	for (int i = 0; i < config->len.total_players; ++i)
	{
		if (players[i].team.id != players[id].team.id && players[i].status == Alive)
		{
			int new_distance = __calculate_distance(players[id], players[i]);
			if (new_distance < distance || distance == 0) {
				nearest_enemy_id = i;
				distance = new_distance;
			}
		}
	}
	return (&players[nearest_enemy_id]);
}
