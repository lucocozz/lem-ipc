/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_assist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:00:23 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/25 19:00:35 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

void	request_assist(int channel_id, t_player ally, t_player enemy)
{
	t_msgbuff	msg = {0};

	errno = 0;
	msg.type = Assist;
	msg.data[Ally] = ally.uid;
	msg.data[Enemy] = enemy.uid;
	msgsnd(channel_id, &msg, sizeof(t_msgbuff), 0);
	printf("%sAssist requested%s\n", TEXT_ORANGE, TEXT_RESET);
}