/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:46:28 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/25 15:32:34 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

static int	__found_enemy_at(t_config *config, t_player *players, int team_id, int x, int y)
{
	for (int i = 0; i < config->len.total_players; ++i)
		if (players[i].position.x == x && players[i].position.y == y && players[i].team.id != team_id && players[i].status == Alive)
			return (1);
	return (0);
}

static int	__enemy_neighbors(t_config *config, t_player *players, int uid)
{
	int			neighbors = 0;
	t_player	player = players[uid];

	neighbors += __found_enemy_at(config, players, player.team.id, player.position.x - 1, player.position.y);
	neighbors += __found_enemy_at(config, players, player.team.id, player.position.x + 1, player.position.y);
	neighbors += __found_enemy_at(config, players, player.team.id, player.position.x, player.position.y - 1);
	neighbors += __found_enemy_at(config, players, player.team.id, player.position.x, player.position.y + 1);
	if (config->diagonal_kill == true) {
		neighbors += __found_enemy_at(config, players, player.team.id, player.position.x + 1, player.position.y + 1);
		neighbors += __found_enemy_at(config, players, player.team.id, player.position.x - 1, player.position.y - 1);
		neighbors += __found_enemy_at(config, players, player.team.id, player.position.x - 1, player.position.y + 1);
		neighbors += __found_enemy_at(config, players, player.team.id, player.position.x + 1, player.position.y - 1);
	}

	return (neighbors);
}

int	death_check(t_config *config, t_game *game, t_team *teams, t_player *players, int uid)
{
	int team_id = players[uid].team.id;

	if (players[uid].status == Dead) {
		msleep(MOVE_DELAY);
		players[uid].position = (t_point){-1, -1};
		printf("Player %d is removed\n", uid);
		teams[team_id].players_alive--;
		game->players_len--;
		if (teams[team_id].players_alive == 0)
			game->teams_alive--;
		return (2);
	}

	int enemy_neighbors = __enemy_neighbors(config, players, uid);
	if (enemy_neighbors >= 2)
	{
		printf("Player %d is dead\n", uid);
		players[uid].status = Dead;
		msleep(MOVE_DELAY);
		return (1);
	}
	return (0);
}
