/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:34:28 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/20 16:34:37 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

void	clean_process(t_process process)
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
