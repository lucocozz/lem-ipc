/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:04:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/26 15:49:08 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

int g_sig = 0;


void __deamon(t_process process)
{
	pid_t pid = fork();

	if (pid < 0) {
		perror("fork");
		clean_process(process, *process.shm.config.ptr);
		exit(EXIT_FAILURE);
	} else if (pid > 0) {
		clean_process(process, *process.shm.config.ptr);
		exit(EXIT_SUCCESS);
	} else {
		printf("Run as deamon\n");
		setsid();
		umask(0);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
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
	} else {
		if (process.shm.config.ptr->deamon == true)
			__deamon(process);
		sub_process(
			process.shm.config.ptr,
			process.shm.game.ptr,
			process.shm.teams.ptr,
			process.shm.players.ptr
		);
	}
	clean_process(process, *process.shm.config.ptr);
	return (EXIT_SUCCESS);
}
