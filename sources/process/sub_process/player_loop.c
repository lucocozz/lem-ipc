/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:50:01 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/19 16:02:34 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"


void	__waiting_setup(t_game *game)
{
	printf("Player %d is waiting for setup\n", getpid());
	while (game->status == Setuping)
		msleep(1);
}

void	player_loop(t_config *config, t_game *game, t_team *teams, t_player *players, sem_t *sem, int id)
{
	int is_dead = 0;

	__waiting_setup(game);
	printf("Player %d is running\n", getpid());
	while (game->status == Running)
	{
		sem_wait(sem);
		is_dead = death_check(config, game, teams, players, id);
		if (is_dead == 2) {
			sem_post(sem);
			break ;
		} else if (is_dead == 1)
			continue ;

		//? calculer la distance de chaque ennemi puis l'envoyer dans mqueue
		//? si mqueue est vide, se déplacer vers l'ennemi le plus proche
		//? sinon, se déplacer vers l'ennemi le plus proche d'un autre joueur
		t_player *enemy = find_nearest_enemy(config, players, id);
		move_to_enemy(config, players, &players[id], *enemy);

		msleep(MOVE_DELAY);
		sem_post(sem);
		msleep(1);
	}
}
