/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_board.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:59:48 by lcocozza          #+#    #+#             */
/*   Updated: 2023/07/13 16:03:43 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

static void	__print_border_line(t_game *game, char *left_corner, char *right_corner)
{
	printf("%s", left_corner);
	for (int i = 0; i < game->board.width * 2; ++i)
		printf("%s", BORDER_LINE);
	printf("%s\n", right_corner);
}

static int	__who_is_here(t_game *game, t_point iter)
{
	for (int i = 0; i < game->config.players; ++i)
	{
		if ((int)iter.x == (int)game->players[i].position.x
			&& (int)iter.y == (int)game->players[i].position.y)
			return (i);
	}
	return (-1);
}

void	print_board(t_game *game)
{
	t_point	iter;

	__print_border_line(game, BORDER_TOP_LEFT, BORDER_TOP_RIGHT);
	for (iter.y = 0; iter.y < game->board.height; ++iter.y)
	{
		printf("%s", BORDER_COLUMN);
		for (iter.x = 0; iter.x < game->board.width; ++iter.x)
		{
			int	is_here = __who_is_here(game, iter);

			if (is_here == -1)
				printf("  ");
			else if (game->players[is_here].status == Alive)
				printf("%s", game->players[is_here].team.icon);
			else
				printf("%s", DEATH_ICON);
		}
		printf("%s\n", BORDER_COLUMN);
	}
	__print_border_line(game, BORDER_BOTTOM_LEFT, BORDER_BOTTOM_RIGHT);
}
