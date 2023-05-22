/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_polygons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:09:28 by lcocozza          #+#    #+#             */
/*   Updated: 2023/05/22 17:20:13 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

void	free_polygons(t_polygon *polygons, int len)
{
	for (int i = 0; i < len; ++i)
		free(polygons[i].vertices);
	free(polygons);
}
