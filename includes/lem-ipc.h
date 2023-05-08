/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:03:35 by lucocozz          #+#    #+#             */
/*   Updated: 2023/05/08 17:36:00 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IPC_H
# define LEM_IPC_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# define EXIT_ERROR 2

# define BOARD_WIDTH 10
# define BOARD_HEIGHT 10
# define TEAM_SIZE 4
# define TEAMS (t_team[]){			\
	{.value = '1', .icon = "🤠"}, 	\
	{.value = '2', .icon = "🥸"}	\
}
# define DEATH_ICON "💀"

# define LEN(x) (sizeof(x) / sizeof(*x))

typedef struct s_team {
	char	value;
	char	*icon;
}	t_team;

#endif
