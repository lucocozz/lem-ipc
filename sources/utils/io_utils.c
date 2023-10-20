/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:58:23 by lucocozz          #+#    #+#             */
/*   Updated: 2023/10/20 14:50:56 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "lem-ipc.h"

char	*read_file(const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
		return (NULL);

	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *result = strdup("");

	while ((read = getline(&line, &len, file)) != -1) {
		result = realloc(result, strlen(result) + read + 1);
		if (result == NULL)
			return (NULL);
		strcat(result, line);
	}

	free(line);
	fclose(file);

	return (result);
}
