/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:54:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/20 00:52:01 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_alive(t_philo *me)
{
	dprintf(2, "(%d) is checking if alive\n", me->id);
	pthread_mutex_lock(&me->is_dead_mutex);
	if (me->is_dead)
	{
		pthread_mutex_unlock(&me->is_dead_mutex);
		return (false);
	}
	if (get_timestamp(me->last_meal) > (unsigned long long)me->rules->time_to_die_ms)
	{
		me->is_dead = true;
		pthread_mutex_unlock(&me->is_dead_mutex);
		usleep(DFLT_PRINT_DELAY_US);
		printf("%llu %d %s\n", get_timestamp(me->last_meal), me->id, MSG_DEAD);
		return (false);
	}
	pthread_mutex_unlock(&me->is_dead_mutex);
	return (true);
}

bool	print_if_alive(t_philo *me, useconds_t print_delay, const char *msg)
{
	(void)print_delay;
	// if (print_delay > 0)
	// 	usleep(print_delay);
	if (!check_alive(me))
		return (false);
	printf("%llu %d %s\n", get_timestamp(me->start_time), me->id, msg);
	return (true);
}

static void	philo_release_forks(t_philo *me)
{
	pthread_mutex_unlock(me->left_fork);
	pthread_mutex_unlock(me->right_fork);
}

static bool	philo_take_fork(t_philo *me, pthread_mutex_t *fork)
{
	return (pthread_mutex_lock(fork) != 0 &&
			print_if_alive(me, DFLT_PRINT_DELAY_US, MSG_FORK));
}

static bool	philo_take_forks(t_philo *me)
{
	return (philo_take_fork(me, me->left_fork) &&
			philo_take_fork(me, me->right_fork));
}

static bool	philo_eat(t_philo *me)
{
	if (!philo_take_forks(me))
		return (false);
	if (!print_if_alive(me, DFLT_PRINT_DELAY_US, MSG_EAT))
		return (false);
	usleep(me->rules->time_to_eat_ms * 1000);
	philo_release_forks(me);
	gettimeofday(&me->last_meal, NULL);
	return (true);
}

static bool	philo_sleep(t_philo *me)
{
	if (!print_if_alive(me, DFLT_PRINT_DELAY_US, MSG_SLEEP))
		return (false);
	usleep(me->rules->time_to_sleep_ms * 1000);
	return (true);
}

static bool	philo_think(t_philo *me, useconds_t thinking_time_us)
{
	if (thinking_time_us)
		usleep(thinking_time_us);
	return (print_if_alive(me, DFLT_PRINT_DELAY_US, MSG_THINK));
}

// Need a value in the philo struct that tell me how long to think in the beginning
void	*philosopher(void *arg)
{
	t_philo			*me;

	me = (t_philo *)arg;

	dprintf(2, "(%d) waits at barrier\n", me->id);

	if (barrier_wait(me->start_barrier) != 0)
		return (NULL);	// IDK yet

	dprintf(2, "(%d) passed the barrier\n", me->id);

	gettimeofday(&me->start_time, NULL);
	me->last_meal = me->start_time;
	if (me->initial_think_us)
		if (!philo_think(me, me->initial_think_us))
			return (NULL);
	while (true)
	{
		if (!philo_eat(me))
			break;
		if (!philo_sleep(me))
			break;
		if (!philo_think(me, 0))
			break;
	}
	return (NULL);
}
