/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:54:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/06 04:43:49 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

static void	*monitor_stop(void *arg);
static void	clean_exit(t_philo *me, pthread_t *monitor_thread, t_exit status);

void	philosopher(t_philo *me)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &monitor_stop, me) != 0)
		clean_exit(me, NULL, THREAD_FAILURE);
	if (VERBOSE)
		print_verbose(me, "has started routine");
	me->cycle_target_time = *me->start_time;
	if (me->initial_think_time_us)
		if (!philo_think_initial(me))
			clean_exit(me, &monitor_thread, SUCCESS);
	increase_target_time(&me->cycle_target_time, me->initial_cycle_time_us);
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
	clean_exit(me, &monitor_thread, SUCCESS);
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

static void	clean_exit(t_philo *me, pthread_t *monitor_thread, t_exit status)
{
	sem_post(me->semaphores->stop.sem);
	if (status == THREAD_FAILURE)
	{
		ft_putstr_fd(ERR_THREAD, STDERR_FILENO);
		sem_post(me->semaphores->dead.sem);
	}
	if (monitor_thread)
		pthread_join(*monitor_thread, NULL);
	sem_post(me->semaphores->exit_ready.sem);
	if (!me->is_dead)
	{
		sem_wait(me->semaphores->exit_allowed.sem);
		sem_post(me->semaphores->exit_allowed.sem);
	}
	if (VERBOSE)
		print_verbose(me, "has exited routine");
	destroy_semaphores(me->semaphores);
	free(me->base_ptr);
	exit(status);
}
