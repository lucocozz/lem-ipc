/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:04:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/20 15:36:08 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

int g_sig = 0;

void	__clean_process(t_process process)
{
	shmdt(process.shm.config.ptr);
	shmdt(process.shm.players.ptr);
	shmdt(process.shm.game.ptr);
	shmdt(process.shm.teams.ptr);
	if (process.type == Master)
	{
		shmctl(process.shm.config.id, IPC_RMID, NULL);
		shmctl(process.shm.players.id, IPC_RMID, NULL);
		shmctl(process.shm.game.id, IPC_RMID, NULL);
		shmctl(process.shm.teams.id, IPC_RMID, NULL);
	}
}

int	main(int argc, char **argv)
{
	t_process	process = init_process(argc, argv);

	if (process.type == Master) {
		master_process(
			process.shm.config.ptr,
			process.shm.game.ptr,
			process.shm.teams.ptr,
			process.shm.players.ptr
		);
	}
	else {
		sub_process(
			process.shm.config.ptr,
			process.shm.game.ptr,
			process.shm.teams.ptr,
			process.shm.players.ptr
		);
	}
	__clean_process(process);
	return (EXIT_SUCCESS);
}
