/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:34:28 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/25 18:42:48 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

void	clean_process(t_process process, t_config config)
{
	shmdt(process.shm.config.ptr);
	shmdt(process.shm.players.ptr);
	shmdt(process.shm.game.ptr);
	shmdt(process.shm.teams.ptr);
	if (process.type == Master)
	{
		for (int i = 0; i < config.len.teams; ++i) {
			int channel_id = msgget(MSGQ_BASE_KEY + i, MSG_PERMS);
			msgctl(channel_id, IPC_RMID, NULL);
		}
		shmctl(process.shm.config.id, IPC_RMID, NULL);
		shmctl(process.shm.players.id, IPC_RMID, NULL);
		shmctl(process.shm.game.id, IPC_RMID, NULL);
		shmctl(process.shm.teams.id, IPC_RMID, NULL);
	}
}
