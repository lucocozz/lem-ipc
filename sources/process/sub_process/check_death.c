/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:46:28 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/17 17:49:36 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

t_player	*__found_enemy_at(t_config *config, t_player *players, int team_id, int x, int y)
{
	for (int i = 0; i < config->len.total_players; ++i)
		if (players[i].position.x == x && players[i].position.y == y && players[i].team.id != team_id)
			return (&players[i]);
	return (NULL);
}

int	__enemy_neighbors(t_config *config, t_game *game, t_player *players, int id)
{
	int			neighbors = 0;
	t_player	player = players[id];

	if (__found_enemy_at(config, players, player.team.id, player.position.x - 1, player.position.y))
		neighbors++;
	if (__found_enemy_at(config, players, player.team.id, player.position.x + 1, player.position.y))
		neighbors++;
	if (__found_enemy_at(config, players, player.team.id, player.position.x, player.position.y - 1))
		neighbors++;
	if (__found_enemy_at(config, players, player.team.id, player.position.x, player.position.y + 1))
		neighbors++;
	return (neighbors);
}

int	check_death(t_config *config, t_game *game, t_player *players, int id)
{
	int enemy_neighbors = __enemy_neighbors(config, game, players, id);
	
	if (enemy_neighbors >= 2)
	{
		printf("Player %d is dead\n", getpid());
		players[id].status = Dead;
		return (1);
	}
	return (0);
}
