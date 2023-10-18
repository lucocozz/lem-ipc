/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:50:01 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/18 18:15:38 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"


void	__waiting_setup(t_game *game)
{
	printf("Player %d is waiting for setup\n", getpid());
	while (game->status == Setuping)
		msleep(1);
}

int __calculate_distance(t_player player, t_player enemy) {
    return abs(enemy.position.x - player.position.x) + abs(enemy.position.y - player.position.y);
}

void __move_to_enemy(t_player *player, t_player enemy)
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

//? are based on the principle that an enemy can always be found.
t_player	*__find_nearest_enemy(t_config *config, t_player *players, int id)
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

void	player_loop(t_config *config, t_game *game, t_player *players, sem_t *sem, int id)
{
	__waiting_setup(game);
	printf("Player %d is running\n", getpid());
	while (game->status == Running)
	{
		sem_wait(sem);
		if (death_check(config, game, players, id)) {
			sem_post(sem);
			break ;
		}
		t_player *enemy = __find_nearest_enemy(config, players, id);
		__move_to_enemy(&players[id], *enemy);
		sem_post(sem);
		msleep(MOVE_DELAY);
	}
}
