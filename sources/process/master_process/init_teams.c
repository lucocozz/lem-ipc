/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_teams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:51:51 by lcocozza          #+#    #+#             */
/*   Updated: 2023/10/18 18:27:08 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"
#define PADDING 4


t_team	*init_teams(int teams_len, int players_len)
{
	t_team	*teams;
	int		emoji_seed = rand_range(0, EMOJIS_LEN);

	teams = malloc(sizeof(t_team) * teams_len);
	if (teams == NULL)
		return (NULL);
	for (int i = 0; i < teams_len; ++i)
	{
		teams[i].id = i;
		teams[i].players_alive = players_len;
		strcpy(teams[i].icon, EMOJIS[(emoji_seed + (i + PADDING)) % EMOJIS_LEN]);
	}
	return (teams);
}
