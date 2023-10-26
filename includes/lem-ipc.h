/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:03:35 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/26 16:02:53 by lucocozz         ###   ########.fr       */
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
# include <sys/msg.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>

# define SHM_GAME_KEY 42001
# define SHM_CONFIG_KEY 42002
# define SHM_PLAYERS_KEY 42003
# define SHM_TEAMS_KEY 42004
# define SEM_NAME "/lem-ipc"
# define MSGQ_BASE_KEY 42100
# define SHM_PERMS 0600
# define MSG_PERMS 0666
# define MAX_TEAMS 20
# define MOVE_DELAY 100
# define REFRESH_DELAY 50
# define MAX_TURN_STUCK 3

# define EXIT_ERROR 2
# define DFT_REL_TOL 1e-9
# define DFT_ABS_TOL 0

# define HELP_USAGE																				\
"Usage:\n"																						\
"As master:\n"																					\
"  ./lem-ipc [ --help ] [ --teams=num ] [ --players=num ] [ --height=num ] [ --width=num ]\n"	\
"\n Options:\n"																					\
"  --help\t\tdisplay this help\n"																\
"  --teams\t\tnumber of teams\n"																\
"  --players\t\tnumber of players per team\n"													\
"  --height\t\theight of the board\n"															\
"  --width\t\twidth of the board\n"																\
"  --diagonal-kill\tallow diagonal kill\n"														\
"  --one-move\t\tallow one move per turn\n"														\
"\n\nAs sub:\n"																					\
"  ./lem-ipc [ --help ] [ --all ] [ --deamon ]\n"												\
"\n Options:\n"																					\
"  --help\tdisplay this help\n"																	\
"  --deamon\tstart process as deamon\n"

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

# define TEXT_BOLD "\e[1m"
# define TEXT_RESET "\e[0m"
# define TEXT_RED "\e[31m"
# define TEXT_GREEN "\e[32m"
# define TEXT_ORANGE "\e[33m"

# define EMOJIS (char *[]){	\
	"😀", "😁", "😆", "😅", "😂", "🤣", "🥲", "😸", "😊", "😇", "🙂", "🙃", \
	"😉", "😌", "😍", "🥰", "😘", "😚", "😋", "👿", "😝", "😜", "🤪", "🤨", \
	"🧐", "🤓", "😎", "🥸", "🤩", "🥳", "😏", "😒", "😞", "🙁", "😣", "😖", \
	"😩", "🥺", "😢", "😭", "😤", "😠", "😡", "😶", "🤯", "😳", "🥵", "😾", \
	"🥶", "😱", "🤭", "😰", "👽", "👾", "🫣", "🤗", "🫡", "😽", "🫢", "😨", \
	"🤫", "🤥", "🤬", "😐", "😬", "🫠", "🙄", "😯", "😦", "🥱", "😴", "🤖", \
	"😪", "😵", "🫥", "🤐", "🥴", "🤢", "🤮", "🤧", "😷", "🤒", "🤕", "😿", \
	"🤑", "🤠", "😈", "😛", "👹", "👺", "🤡", "💩", "👻", "😥", "🎃", "🤤", \
	"😓", "😺", "🥹", "😹", "😻", "😼", "🤔", "🙀" \
}
# define EMOJIS_LEN LEN(EMOJIS)
# define DEATH_ICON "💀"

# define LEN(x) (sizeof(x) / sizeof(*x))
# define msleep(msec) usleep(msec * 1000)

typedef enum e_player_status {
	Waiting,
	Alive,
	Dead
}	t_player_status;

typedef enum e_game_status {
	Setuping,
	Running,
	Finished
}	t_game_status;

typedef enum e_ptype {
	Master,
	Sub
} t_ptype;

typedef enum e_msgtype {
	Assist = 1
}	t_msgtype;

typedef enum e_msg_assist_field {
	Ally = 0,
	Enemy = 1
}	t_msg_assist_field;

typedef struct s_team {
	short	id;
	char	icon[5];
	int		players_alive;
}	t_team;

typedef struct s_fpoint {
	float	x;
	float	y;
}	t_fpoint;

typedef struct s_point {
	int	x;
	int	y;
}	t_point;

typedef struct s_polygon {
	int			len;
	t_fpoint	*vertices;
}	t_polygon;

typedef struct s_player {
	t_point			position;
	t_team			team;
	t_player_status	status;
	pid_t			pid;
	uid_t			uid;
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
	bool	diagonal_kill;
	bool	one_move;
} t_config;

typedef struct s_game {
	int				teams_alive;
	char			**board;
	t_game_status	status;
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

	struct {
		t_team		*ptr;
		key_t		id;
	} teams;
}	t_shm;

typedef struct s_msgbuff {
	long	type;
	int8_t	data[32];
}	t_msgbuff;

typedef struct s_process {
	t_ptype	type;
	t_shm	shm;
}	t_process;

extern int g_sig;

/*  BOARD  */
int 		divide_board_equal_area(t_polygon **areas, int width, int height, int n);
void		free_polygons(t_polygon *polygons, int len);
int			area_id_is(t_polygon *areas, int len, t_point point);
double		halton_sequence(int index, int base);
void		spread_players(t_config *config, t_team *teams, t_player *players, t_polygon *areas, int areas_len);
void		print_board(t_config *config, t_player *players);


/*  UTILS  */
bool	isnear(double a, double b, double relative_tolerance, double absolute_tolerance);
bool	start_with(const char *start_with, const char *str);
int		rand_range(int min, int max);
int		manhattan_distance(t_point pos1, t_point pos2);
char	*read_file(const char *filename);
void	sig_handler(int sig);


/*  PARSER  */
void	parse_config(t_process *process, int argc, char **argv);


/* PROCESS */
t_process	init_process(int argc, char **argv);
void		clean_process(t_process process, t_config config);



/* MASTER PROCESS */
int		master_process(t_config *config, t_game *game, t_team *teams, t_player *players);
void	init_teams(t_team *teams, int teams_len, int players_len);
void	waiting_players(t_config *config, t_game *game, t_player *players, char *title);
void	game_loop(t_config *config, t_game *game, t_player *players, char *title);


/* SUB PROCESS */
void		sub_process(t_config *config, t_game *game, t_team *teams, t_player *players);
void		player_loop(t_config *config, t_game *game, t_team *teams, t_player *players, sem_t *sem, int uid);
int			death_check(t_config *config, t_game *game, t_team *teams, t_player *players, int uid);
int			move_to_enemy(t_config *config, t_player *players, t_player *player, t_player enemy);
t_player	*find_nearest_enemy(t_config *config, t_player *players, int uid);
t_player	*find_nearest_ally_to_enemy(t_config *config, t_player *players, int uid, t_player enemy);
t_player	*get_enemy(t_config *config, t_player *players, int uid, t_player **locked_enemy, int channel_id);
void		request_assist(int channel_id, t_player ally, t_player enemy);

#endif
