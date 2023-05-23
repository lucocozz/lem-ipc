/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area_id_is.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:50:35 by lcocozza          #+#    #+#             */
/*   Updated: 2023/05/23 14:59:54 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

static bool __is_point_inside_polygon(t_point point, const t_polygon polygon)
{
	int				num_vertices = polygon.len;
	const t_point	*vertices = polygon.vertices;

	int i, j;
	bool inside = false;

	for (i = 0, j = num_vertices - 1; i < num_vertices; j = i++) {
		if ((vertices[i].y > point.y) != (vertices[j].y > point.y) &&
			(point.x < (vertices[j].x - vertices[i].x) * (point.y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x)) {
			inside = !inside;
		}
	}

	return (inside);
}

int	area_id_is(t_polygon *areas, int len, t_point point)
{
	for (int i = 0; i < len; ++i) {
		if (__is_point_inside_polygon(point, areas[i]) == true)
			return (i);
	}
	return (-1);
}
