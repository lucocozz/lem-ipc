/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:04:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/05/23 17:34:35 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

int	main()
{
	if (TEAMS_LEN < 2) {
		fprintf(stderr, "Error: minimum of 2 teams is required\n");
		return (EXIT_ERROR);
	}

	printf("╭────────╮\n");
	printf("│%s %s %s│\n", TEAMS[0].icon, TEAMS[1].icon, DEATH_ICON);
	printf("╰────────╯\n");

	t_polygon	*areas = NULL;
	int areas_len = divide_rectangle_equal_area(&areas, BOARD_WIDTH, BOARD_HEIGHT, 5);
	printf("%d\n", areas_len);

	for (int i = 0; i < areas_len; ++i) {
		printf("polygon %d:\n  ", i);
		for (int j = 0; j < areas[i].len; ++j)
			printf("Point(%.0f, %.0f) ", areas[i].vertices[j].x, areas[i].vertices[j].y);
		printf("\n");
	}

	printf("\n");
	for (int y = 0; y < BOARD_HEIGHT; ++y) {
		for (int x = 0; x < BOARD_WIDTH; ++x)
			printf(" %d", area_id_is(areas, areas_len, (t_point){x, y}));
		printf("\n");
	}

	free_polygons(areas, areas_len);
	return (EXIT_SUCCESS);
}
