/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:55:06 by ldulling          #+#    #+#             */
/*   Updated: 2024/07/30 01:33:02 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor_priv.h"

static bool	monitor_dead(void *arg);
static void	*monitor_full(void *arg);
static bool	is_monitor_released(t_mon *monitor);
static void	release_monitor(t_mon *monitor, sem_t *release);

// Split the monitoring for the full and dead semaphores into two threads.
// Only one of them will get enough sem_posts to continue.
bool	monitor(t_mon *monitor)
{
	pthread_t	monitor_thread;
	bool		ret;

	if (pthread_create(&monitor_thread, NULL, &monitor_full, monitor) != 0)
		return (false);
	ret = monitor_dead(monitor);
	pthread_join(monitor_thread, NULL);
	return (ret);
}

static bool	monitor_dead(void *arg)
{
	t_mon	*monitor;

	monitor = (t_mon *)arg;
	sem_wait(monitor->semaphores->dead.sem);
	if (is_monitor_released(monitor))
		return (true);
	release_monitor(monitor, monitor->semaphores->full.sem);
	if (VERBOSE)
		print_verbose_monitor(monitor, "detected a philo died");
	return (broadcast_death(monitor));
}

static void	*monitor_full(void *arg)
{
	t_mon	*monitor;
	int		i;

	monitor = (t_mon *)arg;
	i = 0;
	while (i < monitor->rules->num_of_philos)
	{
		sem_wait(monitor->semaphores->full.sem);
		if (is_monitor_released(monitor))
			return (NULL);
		i++;
	}
	release_monitor(monitor, monitor->semaphores->dead.sem);
	if (VERBOSE)
		print_verbose_monitor(monitor, "detected all philos got full");
	return (NULL);
}

static bool	is_monitor_released(t_mon *monitor)
{
	bool	ret;

	sem_wait(monitor->semaphores->mon_mutex.sem);
	ret = monitor->is_released;
	sem_post(monitor->semaphores->mon_mutex.sem);
	return (ret);
}

static void	release_monitor(t_mon *monitor, sem_t *release)
{
	sem_wait(monitor->semaphores->mon_mutex.sem);
	monitor->is_released = true;
	sem_post(monitor->semaphores->mon_mutex.sem);
	sem_post(release);
}
