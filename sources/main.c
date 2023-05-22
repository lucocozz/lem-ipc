/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:04:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/05/22 17:37:43 by lcocozza         ###   ########.fr       */
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
	int areas_len = divide_rectangle_equal_area(&areas, 11, 11, 2);
	printf("%d\n", areas_len);
	free_polygons(areas, areas_len);
	return (EXIT_SUCCESS);
}
