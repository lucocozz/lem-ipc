/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:04:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/16 17:07:17 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

void	__clean_process(t_process process)
{
	if (process.type == Master)
		free(process.shm.game.ptr->teams);
	shmdt(process.shm.config.ptr);
	shmdt(process.shm.players.ptr);
	shmdt(process.shm.game.ptr);
	if (process.type == Master)
	{
		shmctl(process.shm.config.id, IPC_RMID, NULL);
		shmctl(process.shm.players.id, IPC_RMID, NULL);
		shmctl(process.shm.game.id, IPC_RMID, NULL);
	}
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_process	process = init_process(argc, argv);

	if (process.type == Master)
		master_process(process, process.shm.config.ptr, process.shm.players.ptr, process.shm.game.ptr);
	else
		sub_process(process.shm.config.ptr, process.shm.players.ptr, process.shm.game.ptr);
	__clean_process(process);
	return (EXIT_SUCCESS);
}
