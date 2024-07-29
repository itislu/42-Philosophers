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
	sem_unlink(name);
	sem_named->name = name;
	return (true);
}

bool	init_semaphores(t_semaphores *semaphores, int num_of_philos)
{
	memset(semaphores, 0, sizeof(t_semaphores));
	if (!init_semaphore(&semaphores->forks, "philo_forks", num_of_philos)
		|| !init_semaphore(&semaphores->start, "philo_start", 0)
		|| !init_semaphore(&semaphores->stop, "philo_stop", 0)
		|| !init_semaphore(&semaphores->dead, "philo_dead", 0)
		|| !init_semaphore(&semaphores->full, "philo_full", 0)
		|| !init_semaphore(&semaphores->ready_to_exit, "philo_ready_to_exit", 0)
		|| !init_semaphore(&semaphores->exit_allowed, "philo_exit_allowed", 0)
		|| !init_semaphore(&semaphores->mon_mutex, "philo_mon_mutex", 1))
	{
		destroy_semaphores(semaphores);
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
}

void	destroy_semaphores(t_semaphores *semaphores)
{
	t_sem_named	*sem_named;
	int			count;
	int			i;

	sem_named = (t_sem_named *)semaphores;
	count = sizeof(t_semaphores) / sizeof(t_sem_named);
	i = 0;
	while (i < count)
	{
		destroy_semaphore(sem_named);
		sem_named++;
		i++;
	}
}
