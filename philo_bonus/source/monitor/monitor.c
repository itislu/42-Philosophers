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

static int	get_philo_id_with_pid(t_philo *philos, int num_of_philos, pid_t pid)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		if (philos[i].pid == pid)
			break ;
		i++;
	}
	return (i);
}

static bool	release_monitor(sem_t *sem, bool *is_exited)
{
	if (*is_exited)
		return (false);
	*is_exited = true;
	sem_post(sem);
	return (true);
}

void	*monitor_is_full(void *arg)
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

void	*monitor_is_dead(void *arg)
{
	t_philo *philos = (t_philo *)arg;
	t_semaphores *semaphores = philos->semaphores;
	const t_rules *rules = philos->rules;
	int		wstatus;
	pid_t	pid;

	sem_wait(semaphores->is_dead.sem);
	if (!release_monitor(semaphores->is_full.sem, &philos->is_exited))
		return (NULL);
	pid = waitpid(0, &wstatus, 0);
	print_verbose_monitor(philos, "detected a philosopher died");
	broadcast_death(philos, rules->num_of_philos);
	print_death(philos, rules->num_of_philos, get_philo_id_with_pid(
		philos, rules->num_of_philos, pid));
	return (NULL);
}

// Create two monitoring threads.
// On one, monitor the is_full semaphore; on the other, the is_dead semaphore.
// Only one of them will get enough sem_posts to continue.
void	monitor(t_philo *philos)
{
	pthread_t	monitors[2];

	pthread_create(&monitors[0], NULL, &monitor_is_full, philos);
	pthread_create(&monitors[1], NULL, &monitor_is_dead, philos);
	pthread_join(monitors[0], NULL);
	pthread_join(monitors[1], NULL);
}
