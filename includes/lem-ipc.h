/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:03:35 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/16 16:56:02 by lucocozz         ###   ########.fr       */
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
# include <time.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/sem.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

# define SHM_GAME_KEY 42001
# define SHM_CONFIG_KEY 42002
# define SHM_PLAYERS_KEY 42003
# define SEM_NAME "/lem-ipc"
# define PERMS 0600
# define MAX_TEAMS 20

# define EXIT_ERROR 2
# define DFT_REL_TOL 1e-9
# define DFT_ABS_TOL 0

# define HELP_USAGE																				\
"Usage:\n"																						\
"As master:\n"																					\
"  ./lem-ipc [ --help ] [ --teams=num ] [ --players=num ] [ --height=num ] [ --width=num ]\n"	\
"\n Options:\n"																					\
"  --help: display this help\n"																	\
"  --teams: number of teams\n"																	\
"  --players: number of players per team\n"														\
"  --height: height of the board\n"																\
"  --width: width of the board\n"																\
"\nAs sub:\n"																					\
"  ./lem-ipc [ --help ] [ --all ] [ --deamon ]\n"												\
"\n Options:\n"																					\
"  --help: display this help\n"																	\
"  --all: create a deamon process for each player\n"											\
"  --deamon: start process as deamon\n"

# define DFT_TEAMS 2
# define DFT_PLAYERS 4
# define DFT_HEIGHT 15
# define DFT_WIDTH 15

# define BORDER_LINE "─"
# define BORDER_COLUMN "│"
# define BORDER_TOP_LEFT "╭"
# define BORDER_TOP_RIGHT "╮"
# define BORDER_BOTTOM_LEFT "╰"
# define BORDER_BOTTOM_RIGHT "╯"

# define EMOJIS (char *[]){	\
	"😀", "😁", "😆", "😅", "😂", "🤣", "🥲", "😸", "😊", "😇", "🙂", "🙃", \
	"😉", "😌", "😍", "🥰", "😘", "😚", "😋", "👿", "😝", "😜", "🤪", "🤨", \
	"🧐", "🤓", "😎", "🥸", "🤩", "🥳", "😏", "😒", "😞", "🙁", "😣", "😖", \
	"😩", "🥺", "😢", "😭", "😤", "😠", "😡", "😶", "🤯", "😳", "🥵", "😾", \
	"🥶", "😱", "🤭", "😰", "👽", "😓", "🫣", "🤗", "🫡", "😽", "🫢", "😨", \
	"🤫", "🤥", "🤬", "😐", "😬", "🫠", "🙄", "😯", "😦", "🥱", "😴", "🤖", \
	"😪", "😵", "🫥", "🤐", "🥴", "🤢", "🤮", "🤧", "😷", "🤒", "🤕", "😿", \
	"🤑", "🤠", "😈", "😛", "👹", "👺", "🤡", "💩", "👻", "😥", "👾", "🤤", \
	"🎃", "😺", "🥹", "😹", "😻", "😼", "🤔", "🙀" \
}
# define EMOJIS_LEN LEN(EMOJIS)
# define DEATH_ICON "💀"

# define LEN(x) (sizeof(x) / sizeof(*x))

typedef enum e_player_status {
	Waiting,
	Alive,
	Dead
}	t_player_status;

typedef enum e_game_status {
	Running,
	Finished
}	t_game_status;

typedef enum e_ptype {
	Master,
	Sub
} t_ptype;

typedef struct s_team {
	short	id;
	char	icon[5];
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
	t_point			position;
	t_team			team;
	t_player_status	status;
	pid_t			pid;
}	t_player;

typedef struct s_config {
	
	struct {
		int		teams;
		int		players;
		int		total_players;
	} len;
	struct {
		int		width;
		int		height;
	} board;
	bool	all;
	bool	deamon;
} t_config;

typedef struct s_game {
	t_team			*teams;
	char			**board;
	t_game_status	status;
	t_player		*players;
	int				players_len;
}	t_game;

typedef struct s_shm {
	struct {
		t_game		*ptr;
		key_t		id;
	} game;

	struct {
		t_config	*ptr;
		key_t		id;
	} config;

	struct {
		t_player	*ptr;
		key_t		id;
	} players;
}	t_shm;

typedef struct s_process {
	t_ptype	type;
	t_shm	shm;
}	t_process;

/*  BOARD  */
int 		divide_board_equal_area(t_polygon **areas, int width, int height, int n);
void		free_polygons(t_polygon *polygons, int len);
int			area_id_is(t_polygon *areas, int len, t_point point);
double		halton_sequence(int index, int base);
void		spread_players(t_config *config, t_game *game, t_polygon *areas, int areas_len);
void		print_board(t_config *config, t_player *players);



/*  UTILS  */
bool	isnear(double a, double b, double relative_tolerance, double absolute_tolerance);
bool	start_with(const char *start_with, const char *str);
int		rand_range(int min, int max);


/*  PARSER  */
void	parse_config(t_process *process, int argc, char **argv);


/* PROCESS */
t_process	init_process(int argc, char **argv);



/* MASTER PROCESS */
int		master_process(t_process process, t_config *config, t_player *players, t_game *game);
t_team	*init_teams(int teams_len);
void	waiting_players(sem_t *sem, t_config *config, t_game *game);


/* SUB PROCESS */
void	sub_process(t_config *config, t_player *players, t_game *game);

#endif
