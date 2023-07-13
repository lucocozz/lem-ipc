/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:34:14 by lcocozza          #+#    #+#             */
/*   Updated: 2023/07/13 17:23:58 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

static void	__parsing_error(char *msg, int shm_id)
{
	if (shm_id != 0)
		shmctl(shm_id, IPC_RMID, NULL);
	printf("%s", msg);
	exit(EXIT_ERROR);
}

static t_config	__init_config(t_ptype ptype, int shm_id)
{
	t_config config;

	config.process_type = ptype;
	config.shm_id = shm_id;
	config.teams = DFT_TEAMS;
	config.players = DFT_PLAYERS;
	config.board_height = DFT_HEIGHT;
	config.board_width = DFT_WIDTH;
	config.all = false;
	config.deamon = false;
	return (config);
}

static t_config	__parse_master(int argc, char **argv, int shm_id)
{
	t_config config = __init_config(Master, shm_id);

	for (int i = 1; i < argc; ++i)
	{
		if (start_with("--help", argv[i]))
			__parsing_error(HELP_USAGE, shm_id);
		else if (start_with("--teams=", argv[i]))
			config.teams = atoi(argv[i] + strlen("--teams="));
		else if (start_with("--players=", argv[i]))
			config.players = atoi(argv[i] + strlen("--players="));
		else if (start_with("--height=", argv[i]))
			config.board_height = atoi(argv[i] + strlen("--height="));
		else if (start_with("--width=", argv[i]))
			config.board_width = atoi(argv[i] + strlen("--width="));
		else
			__parsing_error(HELP_USAGE, shm_id);
	}

	if (config.teams < 2 || config.teams > MAX_TEAMS)
		__parsing_error("Error: --teams must be >= 2 and <= 20\n", shm_id);
	if (config.players < 2)
		__parsing_error("Error: --players must be >= 2\n", shm_id);
	if (config.board_height < 5)
		__parsing_error("Error: --height must be >= 5\n", shm_id);
	if (config.board_width < 5)
		__parsing_error("Error: --width must be >= 5\n", shm_id);

	return (config);
}

static t_config	__parse_sub(int argc, char **argv)
{
	t_config config = __init_config(Sub, 0);

	for (int i = 1; i < argc; ++i)
	{
		if (start_with("--help", argv[i]))
			__parsing_error(HELP_USAGE, 0);
		else if (start_with("--all", argv[i]))
			config.all = true;
		else if (start_with("--deamon", argv[i]))
			config.deamon = true;
		else
			__parsing_error(HELP_USAGE, 0);
	}
	config.shm_id = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | PERMS);

	return (config);
}

t_config	parse_config(int argc, char **argv)
{
	errno = 0;
	int shm_id = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | IPC_EXCL | PERMS);
	if (errno == 0)
		return (__parse_master(argc, argv, shm_id));
	else if (errno == EEXIST)
		return (__parse_sub(argc, argv));
	else {
		perror("shmget");
		exit(EXIT_ERROR);
	}
}
