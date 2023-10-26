/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_enemy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:58:31 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/25 18:58:57 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

t_player	*get_enemy(t_config *config, t_player *players, int uid,
	t_player **locked_enemy, int channel_id)
{
	t_msgbuff	msg = {0};

	errno = 0;
	if (msgrcv(channel_id, &msg, sizeof(msg.data), Assist, IPC_NOWAIT | MSG_NOERROR) != -1) {
		if (msg.data[Ally] == (int8_t)uid) {
			*locked_enemy = &players[msg.data[Enemy]];
			printf("%sTaking assist request%s\n", TEXT_GREEN, TEXT_RESET);
		}
		else
			msgsnd(channel_id, &msg, sizeof(t_msgbuff), 0);
	}

	if (*locked_enemy != NULL && (*locked_enemy)->status == Alive)
		return (*locked_enemy);
	*locked_enemy = NULL;
	return (find_nearest_enemy(config, players, uid));
}