/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:57:04 by lcocozza          #+#    #+#             */
/*   Updated: 2023/07/13 14:44:16 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

bool	isnear(double a, double b, double relative_tolerance, double absolute_tolerance)
{
	double diff = fabs(a - b);
	double tolerance = fmax(relative_tolerance * fmax(fabs(a), fabs(b)), absolute_tolerance);

	return (diff <= tolerance);
}

int	rand_range(int min, int max)
{
	srand(time(NULL));
	return (rand() % (max - min + 1) + min);
}
