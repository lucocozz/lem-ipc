/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_to_enemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 20:42:50 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/19 18:33:10 by lucocozz         ###   ########.fr       */
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

void	__move_to(t_player *player, t_point delta)
{
	player->position.x += delta.x;
	player->position.y += delta.y;
}

t_point __explore_best_direction(t_config *config, t_player *players,
	t_player *player, t_player enemy, t_point prev_delta)
{
	int min_distance = -1;
	t_point directions[] = {
		{1, 0}, {0, 1}, {-1, 0}, {0, -1},
	};
	int direction_len = LEN(directions);

	t_point best_direction = {0, 0};

	for (int i = 0; i < direction_len; i++) {
		t_point new_delta = directions[i];
		if (new_delta.x == -prev_delta.x && new_delta.y == -prev_delta.y)
			continue;
		
		t_point new_position = {player->position.x + new_delta.x, player->position.y + new_delta.y};
		if (__can_move(config, players, new_position)) {
			int new_distance = manhattan_distance(new_position, enemy.position);

			if (new_distance < min_distance || min_distance == -1) {
				best_direction = new_delta;
				min_distance = new_distance;
			}
		}
	}
	return (best_direction);
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

	if (__can_move(config, players, (t_point){player->position.x + delta.x, player->position.y + delta.y}))
		__move_to(player, delta);
	else if (manhattan_distance(player->position, enemy.position) > 1) {
		t_point best_direction = __explore_best_direction(config, players, player, enemy, delta);
		__move_to(player, best_direction);
	}
}