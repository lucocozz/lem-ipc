/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:26:52 by lcocozza          #+#    #+#             */
/*   Updated: 2023/07/31 18:09:22 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

t_process	init_process(int argc, char **argv)
{
	t_process process;

	parse_config(&process, argc, argv);
	process.shm.players.id = shmget(SHM_PLAYERS_KEY, sizeof(t_player) *
		process.shm.config.ptr->len.total_players, IPC_CREAT | PERMS);
	process.shm.players.ptr = shmat(process.shm.players.id, NULL, 0);
	process.shm.game.id = shmget(SHM_GAME_KEY, sizeof(t_game), IPC_CREAT | PERMS);
	process.shm.game.ptr = shmat(process.shm.game.id, NULL, 0);
	return (process);
}