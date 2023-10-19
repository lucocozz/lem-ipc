/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_to_enemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 20:42:50 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/19 16:22:44 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

int		__can_move(t_config *config, t_player *players, t_point point)
{
	if (point.x < 0 || point.y < 0 || point.x >= config->board.width || point.y >= config->board.height)
		return (false);
	for (int i = 0; i < config->len.total_players; ++i)
	{
		if (players[i].position.x == point.x && players[i].position.y == point.y)
			return (false);
	}
	return (true);
}

void	move_to_enemy(t_config *config, t_player *players, t_player *player, t_player enemy)
{
	t_point delta = {
		.x = enemy.position.x - player->position.x,
		.y = enemy.position.y - player->position.y
	};

	if (abs(delta.x) > abs(delta.y)) {
		delta.x = (delta.x > 0) ? 1 : -1;
		delta.y = 0;
	}
	else {
		delta.y = (delta.y > 0) ? 1 : -1;
		delta.x = 0;
	}

	if (!__can_move(config, players, (t_point){player->position.x + delta.x, player->position.y + delta.y}))
		return ;
	player->position.x += delta.x;
	player->position.y += delta.y;
}