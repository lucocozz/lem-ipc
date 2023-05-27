/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:03:35 by lucocozz          #+#    #+#             */
/*   Updated: 2023/05/27 20:33:08 by lucocozz         ###   ########.fr       */
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

# define BORDER_LINE_LEN BOARD_WIDTH * 2
# define BORDER_LINE "─"
# define BORDER_COLUMN "│"
# define BORDER_TOP_LEFT "╭"
# define BORDER_TOP_RIGHT "╮"
# define BORDER_BOTTOM_LEFT "╰"
# define BORDER_BOTTOM_RIGHT "╯"

# define BOARD_WIDTH 30
# define BOARD_HEIGHT 30
# define PLAYERS_NUM (int)(TEAM_SIZE * TEAMS_LEN)
# define TEAM_SIZE 10
# define TEAMS_LEN LEN(TEAMS)
# define TEAMS (t_team[]){			\
	{.value = 1, .icon = "🤠"}, 	\
	{.value = 2, .icon = "🥸"},		\
	{.value = 3, .icon = "🤓"},		\
	{.value = 4, .icon = "🧐"}		\
}
# define DEATH_ICON "💀"

# define LEN(x) (sizeof(x) / sizeof(*x))

typedef enum e_status {
	Alive,
	Dead
}	t_status;

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

typedef struct s_player {
	t_point		position;
	t_team		team;
	t_status	status;
}	t_player;


/*  BOARD  */
int 		divide_board_equal_area(t_polygon **areas, int width, int height, int n);
void		free_polygons(t_polygon *polygons, int len);
int			area_id_is(t_polygon *areas, int len, t_point point);
double		halton_sequence(int index, int base);
t_player	*spread_players(t_polygon *areas, int areas_len);
void		print_board(t_player *players);


/*  UTILS  */
bool	isclose(double a, double b, double relative_tolerance, double absolute_tolerance);

#endif
