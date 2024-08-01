/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_semaphores.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:20:12 by ldulling          #+#    #+#             */
/*   Updated: 2024/07/31 18:32:28 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

static bool	init_semaphore(t_sem_named *sem_named, char *name, int value);
static void	destroy_semaphore(t_sem_named *sem_named);

bool	init_semaphores(t_semaphores *semaphores, int num_of_philos)
{
	memset(semaphores, 0, sizeof(t_semaphores));
	if (!init_semaphore(&semaphores->forks, "/philo_forks", num_of_philos)
		|| !init_semaphore(&semaphores->stop, "/philo_stop", 0)
		|| !init_semaphore(&semaphores->dead, "/philo_dead", 0)
		|| !init_semaphore(&semaphores->full, "/philo_full", 0)
		|| !init_semaphore(&semaphores->exit_ready, "/philo_exit_ready", 0)
		|| !init_semaphore(&semaphores->exit_allowed, "/philo_exit_allowed", 0)
		|| !init_semaphore(&semaphores->mon_mutex, "/philo_mon_mutex", 1)
		|| !init_semaphore(&semaphores->philo_mutex, "/philo_philo_mutex", 1))
	{
		destroy_semaphores(semaphores);
		return (false);
	}
	return (true);
}

static bool	init_semaphore(t_sem_named *sem_named, char *name, int value)
{
	sem_unlink(name);
	sem_named->sem = sem_open(name, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, value);
	if (sem_named->sem == SEM_FAILED)
		return (false);
	sem_unlink(name);
	sem_named->name = name;
	return (true);
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

static void	destroy_semaphore(t_sem_named *sem_named)
{
	if (!sem_named->sem)
		return ;
	sem_close(sem_named->sem);
	sem_unlink(sem_named->name);
}
