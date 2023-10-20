/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:04:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/20 16:34:45 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

int g_sig = 0;

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
	clean_process(process);
	return (EXIT_SUCCESS);
}
