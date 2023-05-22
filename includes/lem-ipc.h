/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:03:35 by lucocozz          #+#    #+#             */
/*   Updated: 2023/05/22 17:21:37 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IPC_H
# define LEM_IPC_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <sys/types.h>
# include <stdbool.h>

# define EXIT_ERROR 2
# define DFT_REL_TOL 1e-9
# define DFT_ABS_TOL 0

# define BOARD_WIDTH 10
# define BOARD_HEIGHT 10
# define TEAM_SIZE 4
# define TEAMS_LEN LEN(TEAMS)
# define TEAMS (t_team[]){			\
	{.value = 1, .icon = "🤠"}, 	\
	{.value = 2, .icon = "🥸"}		\
}
# define DEATH_ICON "💀"

# define LEN(x) (sizeof(x) / sizeof(*x))

typedef struct s_team {
	short	value;
	char	*icon;
}	t_team;

typedef struct s_point {
	float	x;
	float	y;
}	t_point;

typedef struct s_polygon {
	int		len;
	t_point	*vertices;
}	t_polygon;


int 	divide_rectangle_equal_area(t_polygon **areas, int width, int height, int n);
void	free_polygons(t_polygon *polygons, int len);


#endif
