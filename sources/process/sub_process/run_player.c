/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:50:01 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/17 18:33:46 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"


void	__waiting_setup(t_game *game)
{
	printf("Player %d is waiting for setup\n", getpid());
	while (game->status == Setuping)
		sleep(1);
}

int __calculate_distance(t_player player, t_player enemy) {
    return abs(enemy.position.x - player.position.x) + abs(enemy.position.y - player.position.y);
}

int __move_to_enemy(t_player *player, t_player enemy)
{
	int dx = enemy.position.x - player->position.x;
	int dy = enemy.position.y - player->position.y;

	if (abs(dx) > 1)
	    dx = (dx > 0) ? 1 : -1;
	if (abs(dy) > 1)
	    dy = (dy > 0) ? 1 : -1;

	player->position.x += dx;
	player->position.y += dy;
}

void	run_player(t_config *config, t_game *game, t_player *players, int id)
{
	__waiting_setup(game);
	printf("Player %d is running\n", getpid());
	while (game->status == Running)
	{
		msleep(50);
		if (__check_death(config, game, players, id))
			break ;
		
	}
}
