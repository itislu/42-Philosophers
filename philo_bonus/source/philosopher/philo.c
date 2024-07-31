/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:54:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/07/30 01:39:18 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

static void	*monitor_stop(void *arg);
static void	clean_exit(t_philo *me, pthread_t monitor);

void	philosopher(t_philo *me)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, &monitor_stop, me);
	if (VERBOSE)
		print_verbose(me, "has started routine");
	if (me->initial_think_time_us)
		if (!philo_think_initial(me))
			clean_exit(me, monitor);
	while (true)
	{
		if (!philo_eat(me))
			break ;
		if (!philo_sleep(me))
			break ;
		if (!philo_think(me))
			break ;
	}
	release_forks(me);
	clean_exit(me, monitor);
}

static void	*monitor_stop(void *arg)
{
	t_philo			*me;
	t_semaphores	*semaphores;

	me = (t_philo *)arg;
	semaphores = me->semaphores;
	sem_wait(semaphores->stop.sem);
	sem_post(semaphores->stop.sem);
	set_is_stopped(me);
	return (NULL);
}

static void	clean_exit(t_philo *me, pthread_t monitor)
{
	int	exit_status;

	sem_post(me->semaphores->stop.sem);
	pthread_join(monitor, NULL);
	sem_post(me->semaphores->exit_ready.sem);
	if (!me->is_dead)
	{
		sem_wait(me->semaphores->exit_allowed.sem);
		sem_post(me->semaphores->exit_allowed.sem);
	}
	exit_status = me->is_dead;
	if (VERBOSE)
		print_verbose(me, "has exited routine");
	destroy_semaphores(me->semaphores);
	free(me->base_ptr);
	exit(exit_status);
}
