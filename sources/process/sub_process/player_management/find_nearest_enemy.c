/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_nearest_enemy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 20:44:54 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/24 19:27:55 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

t_player	*find_nearest_enemy(t_config *config, t_player *players, int uid)
{
	int distance = 0;
	int nearest_enemy_id = -1;

	for (int i = 0; i < config->len.total_players; ++i)
	{
		if (players[i].team.id != players[uid].team.id && players[i].status == Alive)
		{
			int new_distance = manhattan_distance(players[uid].position, players[i].position);
			if (new_distance < distance || distance == 0) {
				nearest_enemy_id = i;
				distance = new_distance;
			}
		}
	}
	if (nearest_enemy_id == -1)
		return (NULL);
	return (&players[nearest_enemy_id]);
}
