/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcocozza <lcocozza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:45:12 by lcocozza          #+#    #+#             */
/*   Updated: 2023/07/17 17:55:55 by lcocozza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-ipc.h"

void	*quick_shm_alloc(size_t size, key_t key)
{
	int		shm_id;
	void	*shm;

	shm_id = shmget(key, size, IPC_CREAT | 0666);
	if (shm_id == -1)
		return (NULL);
	shm = shmat(shm_id, NULL, 0);
	if (shm == (void *)-1)
		return (NULL);
	// shmctl(shm_id, IPC_RMID, NULL);
	return (shm);
}
