/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:04:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/05/28 18:44:20 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

int	main()
{
	t_player	*players;
	t_polygon	*areas = NULL;
	int			areas_len;

	if (TEAMS_LEN < 2) {
		fprintf(stderr, "Error: minimum of 2 teams is required\n");
		return (EXIT_ERROR);
	}

	areas_len = divide_board_equal_area(&areas, BOARD_WIDTH, BOARD_HEIGHT, TEAMS_LEN);
	players = spread_players(areas, areas_len);

	print_board(players);

	free(players);
	free_polygons(areas, areas_len);
	return (EXIT_SUCCESS);
}
