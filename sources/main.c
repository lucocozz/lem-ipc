/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:04:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/07/17 16:36:33 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

int	main(int argc, char **argv)
{
	t_config	config = parse_config(argc, argv);
	t_game		*game = shmat(config.shm_id, NULL, 0);

	if (config.process_type == Master)
		master_process(config, game);
	else
		sub_process(config, game);

	// free(players);
	// free_polygons(areas, areas_len);
	// shmctl(shm_id, IPC_RMID, NULL);
	return (EXIT_SUCCESS);
}
