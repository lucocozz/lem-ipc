/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:31:13 by lcocozza          #+#    #+#             */
/*   Updated: 2023/07/12 10:33:05 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __USE_MISC

#include <sys/types.h>
#include <stdbool.h>

bool	start_with(const char *start_with, const char *str)
{
	uint	i = 0;

	while (start_with[i] != '\0' && str[i] != '\0') {
		if (start_with[i] != str[i])
			return (false);
		++i;
	}
	return (start_with[i] == '\0' ? true : false);
}
