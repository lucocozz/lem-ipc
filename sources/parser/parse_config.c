/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:34:14 by lcocozza          #+#    #+#             */
/*   Updated: 2023/07/31 19:03:31 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

static void	__parsing_exit(int status, char *msg, int shm_id)
{
	if (shm_id != 0)
		shmctl(shm_id, IPC_RMID, NULL);
	printf("%s", msg);
	exit(status);
}

static void	__init_config(t_config *config)
{
	config->len.teams = DFT_TEAMS;
	config->len.players = DFT_PLAYERS;
	config->board.height = DFT_HEIGHT;
	config->board.width = DFT_WIDTH;
	config->all = false;
	config->deamon = false;
}

static void	__parse_master(t_config *config, key_t shm_id, int argc, char **argv)
{
	__init_config(config);
	for (int i = 1; i < argc; ++i)
	{
		if (start_with("--help", argv[i]))
			__parsing_exit(EXIT_SUCCESS, HELP_USAGE, shm_id);
		else if (start_with("--teams=", argv[i]))
			config->len.teams = atoi(argv[i] + strlen("--teams="));
		else if (start_with("--players=", argv[i]))
			config->len.players = atoi(argv[i] + strlen("--players="));
		else if (start_with("--height=", argv[i]))
			config->board.height = atoi(argv[i] + strlen("--height="));
		else if (start_with("--width=", argv[i]))
			config->board.width = atoi(argv[i] + strlen("--width="));
		else
			__parsing_exit(EXIT_ERROR, HELP_USAGE, shm_id);
	}

	if (config->len.teams < 2 || config->len.teams > MAX_TEAMS)
		__parsing_exit(EXIT_ERROR, "Error: --teams must be >= 2 and <= 20\n", shm_id);
	if (config->len.players < 2)
		__parsing_exit(EXIT_ERROR, "Error: --players must be >= 2\n", shm_id);
	if (config->board.height < 5)
		__parsing_exit(EXIT_ERROR, "Error: --height must be >= 5\n", shm_id);
	if (config->board.width < 5)
		__parsing_exit(EXIT_ERROR, "Error: --width must be >= 5\n", shm_id);
	config->len.total_players = config->len.teams * config->len.players;
}

static void	__parse_sub(t_config *config, int argc, char **argv)
{
	for (int i = 1; i < argc; ++i)
	{
		if (start_with("--help", argv[i]))
			__parsing_exit(EXIT_SUCCESS, HELP_USAGE, 0);
		else if (start_with("--all", argv[i]))
			config->all = true;
		else if (start_with("--deamon", argv[i]))
			config->deamon = true;
		else
			__parsing_exit(EXIT_ERROR, HELP_USAGE, 0);
	}
}

void	parse_config(t_process *process, int argc, char **argv)
{
	errno = 0;
	process->shm.config.id = shmget(SHM_CONFIG_KEY, sizeof(t_config), IPC_CREAT | IPC_EXCL | PERMS);
	if (errno == 0) {
		process->type = Master;
		process->shm.config.ptr = shmat(process->shm.config.id, NULL, 0);
		return (__parse_master(process->shm.config.ptr, process->shm.config.id, argc, argv));
	}
	else if (errno == EEXIST) {
		process->type = Sub;
		process->shm.config.id = shmget(SHM_CONFIG_KEY, sizeof(t_config), 0);
		process->shm.config.ptr = shmat(process->shm.config.id, NULL, 0);
		return (__parse_sub(process->shm.config.ptr, argc, argv));
	}
}
