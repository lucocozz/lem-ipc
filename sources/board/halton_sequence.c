/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   halton_sequence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:48:33 by lcocozza          #+#    #+#             */
/*   Updated: 2023/05/25 13:47:14 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

double  halton_sequence(int index, int base)
{
    double	result = 0;
    double	f = 1.0 / (double)base;
    int		i = index;

    while(i > 0)
	{
        result = result + f * (double)(i % base);
        i = i / base;
        f = f / (double)base;
    }

    return (result);
}
