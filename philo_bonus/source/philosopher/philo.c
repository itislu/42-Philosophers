/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:54:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/06 01:54:19 by ldulling         ###   ########.fr       */
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
	if (VERBOSE)
		print_verbose_us(me, STY_BOL STY_YEL "cycle_target_time: " STY_RES, me->cycle_target_time.tv_sec * 1000 + me->cycle_target_time.tv_usec / 1000 - (me->start_time->tv_sec * 1000 + me->start_time->tv_usec / 1000));
	while (true)
	{
		if (!philo_eat(me))
			break ;
		if (VERBOSE)
			print_verbose_us(me, STY_BOL STY_MAG "cycle_target_time: " STY_RES, me->cycle_target_time.tv_sec * 1000 + me->cycle_target_time.tv_usec / 1000 - (me->start_time->tv_sec * 1000 + me->start_time->tv_usec / 1000));
		if (!philo_sleep(me))
			break ;
		if (VERBOSE)
			print_verbose_us(me, STY_BOL STY_BLU "cycle_target_time: " STY_RES, me->cycle_target_time.tv_sec * 1000 + me->cycle_target_time.tv_usec / 1000 - (me->start_time->tv_sec * 1000 + me->start_time->tv_usec / 1000));
		if (!philo_think(me))
			break ;
		if (VERBOSE)
			print_verbose_us(me, STY_BOL STY_YEL "cycle_target_time: " STY_RES, me->cycle_target_time.tv_sec * 1000 + me->cycle_target_time.tv_usec / 1000 - (me->start_time->tv_sec * 1000 + me->start_time->tv_usec / 1000));
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
