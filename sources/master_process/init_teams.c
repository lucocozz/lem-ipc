/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_teams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:51:51 by lcocozza          #+#    #+#             */
/*   Updated: 2023/07/13 16:54:38 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

t_team	*init_teams(int teams_len)
{
	t_team	*teams;
	int		emoji_seed = rand_range(0, EMOJIS_LEN);

	teams = malloc(sizeof(t_team) * teams_len);
	if (teams == NULL)
		return (NULL);
	for (int i = 0; i < teams_len; ++i)
	{
		teams[i].id = i;
		strcpy(teams[i].icon, EMOJIS[(emoji_seed + i) % EMOJIS_LEN]);
	}
	return (teams);
}
