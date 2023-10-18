/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_teams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:51:51 by lcocozza          #+#    #+#             */
/*   Updated: 2023/10/18 19:14:38 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"
#define PADDING 4


void	init_teams(t_team *teams, int teams_len, int players_len)
{
	int		emoji_seed = rand_range(0, EMOJIS_LEN);

	for (int i = 0; i < teams_len; ++i)
	{
		teams[i].id = i;
		teams[i].players_alive = players_len;
		strcpy(teams[i].icon, EMOJIS[(emoji_seed + (i + PADDING)) % EMOJIS_LEN]);
	}
}
