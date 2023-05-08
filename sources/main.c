/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:04:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/05/08 17:23:08 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

int	main()
{
	if (LEN(TEAMS) < 2) {
		fprintf(stderr, "Error: minimum of 2 teams required\n");
		return (EXIT_ERROR);
	}

	printf("╭──────╮\n");
	printf("│%s%s%s│\n", TEAMS[0].icon, TEAMS[1].icon, DEATH_ICON);
	printf("╰──────╯\n");
	return (EXIT_SUCCESS);
}
