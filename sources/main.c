/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:04:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/07/31 18:55:16 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

int	main(int argc, char **argv)
{
	t_process	process = init_process(argc, argv);

	if (process.type == Master)
		master_process(process.shm.config.ptr, process.shm.players.ptr, process.shm.game.ptr);
	else
		sub_process(process.shm.config.ptr, process.shm.players.ptr, process.shm.game.ptr);

	// free(players);
	// shmctl(shm_id, IPC_RMID, NULL);
	return (EXIT_SUCCESS);
}
