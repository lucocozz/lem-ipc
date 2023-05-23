/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_rectangle_equal_area.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:47:56 by lcocozza          #+#    #+#             */
/*   Updated: 2023/05/23 16:33:05 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

static t_point	*__append_vertex(t_point *vertices, int len, t_point point)
{
	vertices = realloc(vertices, sizeof(t_point) * (len + 1));
	vertices[len] = point;
	return (vertices);
}

static t_polygon	*__append_polygon(t_polygon *polygons, t_point *vertices,
	int polygon_len, int vertices_len)
{
	polygons = realloc(polygons, sizeof(t_polygon) * (polygon_len + 1));
	polygons[polygon_len].vertices = vertices;
	polygons[polygon_len].len = vertices_len;
	return (polygons);
}

static float	__calculate_area(t_point *vertices, int len, int n)
{
	float	area = 0.0;

	for (int i = 0; i < n; ++i) {
		t_point	point_a = vertices[i];
		t_point point_b = vertices[(i + 1) % len];
		area += point_a.x * point_b.y - point_a.y * point_b.x;
	}
	return (area / 2);
}

static t_point	*__create_polygon_rectangle(int width, int height)
{
	t_point	*rectangle = NULL;

	rectangle = __append_vertex(rectangle, 0, (t_point){0, 0});
	rectangle = __append_vertex(rectangle, 1, (t_point){width, 0});
	rectangle = __append_vertex(rectangle, 2, (t_point){width, height});
	rectangle = __append_vertex(rectangle, 3, (t_point){0, height});
	
	return (rectangle);
}

static bool	__isclose(double a, double b, double relative_tolerance, double absolute_tolerance)
{
	double diff = fabs(a - b);
	double tolerance = fmax(relative_tolerance * fmax(fabs(a), fabs(b)), absolute_tolerance);

	return (diff <= tolerance);
}

static void	__reduce_area_to(t_point *vertices, int len, float target_area)
{
	t_point	center = vertices[0];
	t_point	previous_vertex = vertices[len - 2];
	t_point	*current_vertex = &(vertices[len - 1]);

	float	current_area = 2 * __calculate_area(vertices, len, len - 2);
	target_area *= 2;

	if (previous_vertex.x == current_vertex->x) {
		current_vertex->y = (target_area - current_area - current_vertex->x *
			(center.y - previous_vertex.y)) / (previous_vertex.x - center.x);
	}
	else {
		current_vertex->x = (target_area - current_area - current_vertex->y *
			(previous_vertex.x - center.x)) / (center.y - previous_vertex.y);
	}
}

int divide_rectangle_equal_area(t_polygon **areas, int width, int height, int n)
{
	t_point 	*rectangle = __create_polygon_rectangle(width, height);

	if (n == 1) {
		*areas = __append_polygon(*areas, rectangle, 0, 4);
		return (1);
	}

	float	total_area = __calculate_area(rectangle, 4, 4);
	float	target_area_polygon = total_area / n;

	t_point	center_point = {width / 2, height / 2};
	t_point	first_point = {width / 2, 0};

	int	areas_len;
	int next_vertex_index = 0;
	for (areas_len = 0; areas_len < n; ++areas_len)
	{
		int		len = 0;
		t_point	*current_polygon = __append_vertex(NULL, len++, center_point);
		current_polygon = __append_vertex(current_polygon, len++, first_point);

		float	current_area_polygon = 0.0;
		while (current_area_polygon < target_area_polygon)
		{
			next_vertex_index = (next_vertex_index + 1) % 4;
			current_polygon = __append_vertex(current_polygon, len++, rectangle[next_vertex_index]);
			current_area_polygon = __calculate_area(current_polygon, len, len);
		}
		if (__isclose(current_area_polygon, target_area_polygon, DFT_REL_TOL, DFT_ABS_TOL) == false) {
			__reduce_area_to(current_polygon, len, target_area_polygon);
			current_area_polygon = __calculate_area(current_polygon, len, len);
			next_vertex_index = (4 + next_vertex_index - 1) % 4;
		}
		*areas = __append_polygon(*areas, current_polygon, areas_len, len);
		first_point = current_polygon[len - 1];
	}
	free(rectangle);
	return (areas_len);
}
