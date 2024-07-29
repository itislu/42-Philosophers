/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:55:06 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 13:52:48 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor_priv.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

static void	*monitor_is_dead(void *arg);
static void	*monitor_is_full(void *arg);
static bool	release_monitor(sem_t *sem, bool *is_exited);

// Split the monitoring for the is_full and is_dead semaphore into two threads.
// Only one of them will get enough sem_posts to continue.
void	monitor(t_philo *philos)
{
	pthread_t	monitor_thread;

	pthread_create(&monitor_thread, NULL, &monitor_is_full, philos);
	monitor_is_dead(philos);
	pthread_join(monitor_thread, NULL);
}

static void	*monitor_is_full(void *arg)
{
	t_philo			*philos;
	t_semaphores	*semaphores;
	int				i;

	philos = (t_philo *)arg;
	semaphores = philos->semaphores;
	i = 0;
	while (i < philos->rules->num_of_philos)
	{
		sem_wait(semaphores->is_full.sem);
		if (philos->is_exited)
			return (NULL);
		i++;
	}
	if (!release_monitor(semaphores->is_dead.sem, &philos->is_exited))
		return (NULL);
	if (VERBOSE)
		print_verbose_monitor(philos, "detected all philosophers got full");
	return (NULL);
}

static void	*monitor_is_dead(void *arg)
{
	t_philo			*philos;
	t_semaphores	*semaphores;

	philos = (t_philo *)arg;
	semaphores = philos->semaphores;
	sem_wait(semaphores->is_dead.sem);
	if (!release_monitor(semaphores->is_full.sem, &philos->is_exited))
		return (NULL);
	if (VERBOSE)
		print_verbose_monitor(philos, "detected a philosopher died");
	broadcast_death(philos);
	return (NULL);
}

static bool	release_monitor(sem_t *sem, bool *is_exited)
{
	if (*is_exited)
		return (false);
	*is_exited = true;
	sem_post(sem);
	return (true);
}
