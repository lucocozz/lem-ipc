/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:04:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/07/13 11:26:05 by lcocozza         ###   ########.fr       */
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
	// areas_len = divide_board_equal_area(&areas, BOARD_WIDTH, BOARD_HEIGHT, TEAMS_LEN);
	// players = spread_players(areas, areas_len);

	// print_board(players);

	// free(players);
	// free_polygons(areas, areas_len);
	// shmctl(shm_id, IPC_RMID, NULL);
	return (EXIT_SUCCESS);
}
