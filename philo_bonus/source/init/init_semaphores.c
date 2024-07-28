/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:20:12 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 13:47:25 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

bool	init_semaphore(t_sem_named *sem_named, char *name, int value)
{
	sem_unlink(name);
	sem_named->sem = sem_open(name, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, value);
	if (sem_named->sem == SEM_FAILED)
		return (false);
	sem_named->name = name;
	return (true);
}

bool	init_semaphores(t_semaphores *semaphores, int count)
{
	memset(semaphores, 0, sizeof(t_semaphores));
	if (!init_semaphore(&semaphores->forks, "philo_forks", count)
		|| !init_semaphore(&semaphores->sync, "philo_sync", 0)
		|| !init_semaphore(&semaphores->is_dead, "philo_is_dead", 0)
		|| !init_semaphore(&semaphores->is_full, "philo_is_full", 0))
	{
		destroy_semaphores(semaphores, count);
		return (false);
	}
	return (true);
}

void	destroy_semaphore(t_sem_named *sem_named)
{
	if (!sem_named->sem)
		return ;
	sem_close(sem_named->sem);
	sem_unlink(sem_named->name);
	// ft_free_and_null((void **)&sem_named->sem);
}

void	destroy_semaphores(t_semaphores *semaphores, int count)
{
	t_sem_named	*sem_named;
	int			i;

	sem_named = (t_sem_named *)semaphores;
	i = 0;
	while (i < count)
	{
		destroy_semaphore(sem_named);
		sem_named++;
		i++;
	}
}
