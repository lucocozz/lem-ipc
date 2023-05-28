/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_board.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:59:48 by lcocozza          #+#    #+#             */
/*   Updated: 2023/05/28 18:16:59 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

static void	__print_border_line(char *left_corner, char *right_corner)
{
	printf("%s", left_corner);
	for (int i = 0; i < BORDER_LINE_LEN; ++i)
		printf("%s", BORDER_LINE);
	printf("%s\n", right_corner);
}

static int	__who_is_here(t_player *players, t_point iter)
{
	for (int i = 0; i < PLAYERS_NUM; ++i)
	{
		if ((int)iter.x == (int)players[i].position.x
			&& (int)iter.y == (int)players[i].position.y)
			return (i);
	}
	return (-1);
}

void	print_board(t_player *players)
{
	t_point	iter;

	__print_border_line(BORDER_TOP_LEFT, BORDER_TOP_RIGHT);
	for (iter.y = 0; iter.y < BOARD_HEIGHT; ++iter.y)
	{
		printf("%s", BORDER_COLUMN);
		for (iter.x = 0; iter.x < BOARD_WIDTH; ++iter.x)
		{
			int	is_here = __who_is_here(players, iter);

			if (is_here == -1)
				printf("  ");
			else if (players[is_here].status == Alive)
				printf("%s", players[is_here].team.icon);
			else {
				//TODO: remove dead player
				printf("%s", DEATH_ICON);
			}
		}
		printf("%s\n", BORDER_COLUMN);
	}
	__print_border_line(BORDER_BOTTOM_LEFT, BORDER_BOTTOM_RIGHT);
}