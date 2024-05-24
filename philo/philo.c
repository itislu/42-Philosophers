/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:54:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/24 19:25:33 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_alive(t_philo *me)
{
	// print_db(me, "is checking if alive");
	pthread_mutex_lock(&me->state_mutex);
	if (me->state != ALIVE)
	{
		pthread_mutex_unlock(&me->state_mutex);
		return (false);
	}
	if (get_elapsed_time_ms(me->last_meal) > (unsigned long long)me->rules->time_to_die_ms)
	{
		me->state = DYING;
		pthread_mutex_unlock(&me->state_mutex);
		print_db_death(me);
		return (false);
	}
	pthread_mutex_unlock(&me->state_mutex);
	return (true);
}

static void	philo_release_forks(t_philo *me)
{
	if (me->locked_left_fork)
	{
		pthread_mutex_unlock(me->left_fork);
		me->locked_left_fork = false;
	}
	if (me->locked_right_fork)
	{
		pthread_mutex_unlock(me->right_fork);
		me->locked_right_fork = false;
	}
}

static bool	philo_take_fork(t_philo *me, pthread_mutex_t *fork)
{
	// if (!check_alive(me))
	// 	return (false);
	//* The too late death time was bc it was stuck in this mutex
	if (pthread_mutex_lock(fork) != 0)
		return (false);
	// dprintf(2, "%llu %d has locked fork\n", get_elapsed_time_ms(me->start_time), me->id);
	if (!print_if_alive(me, DFLT_PRINT_DELAY_US, MSG_FORK))
	{
		pthread_mutex_unlock(fork);
		return (false);
	}
	return (true);
}

static bool	philo_take_forks(t_philo *me)
{
	print_db(me, "is trying to take forks");
	if (!philo_take_fork(me, me->left_fork))
		return (false);
	me->locked_left_fork = true;
	print_db(me, "has taken left fork");
	if (!philo_take_fork(me, me->right_fork))
		return (false);
	me->locked_right_fork = true;
	print_db(me, "has taken right fork");
	return (true);
}

static bool	philo_eat(t_philo *me)
{
	if (!philo_take_forks(me))
		return (false);

	if (!print_if_alive(me, DFLT_PRINT_DELAY_US, MSG_EAT))
		return (false);
	gettimeofday(&me->last_meal, NULL);
	usleep_while_alive(me->rules->time_to_eat_ms * 1000, me);

	philo_release_forks(me);
	print_db(me, "has released forks");
	return (true);
}

static bool	philo_sleep(t_philo *me)
{
	if (!print_if_alive(me, DFLT_PRINT_DELAY_US, MSG_SLEEP))
		return (false);
	usleep_while_alive(me->rules->time_to_sleep_ms * 1000, me);
	return (true);
}

static bool	philo_think(t_philo *me, useconds_t thinking_time_us)
{
	if (!print_if_alive(me, DFLT_PRINT_DELAY_US, MSG_THINK))
		return (false);
	if (thinking_time_us)
		usleep_while_alive(thinking_time_us, me);
	return (true);
}

// Need a value in the philo struct that tell me how long to think in the beginning
void	*philosopher(void *arg)
{
	t_philo			*me;

	me = (t_philo *)arg;

	gettimeofday(&me->start_time, NULL);
	// print_db(me, "waits at barrier");

	// if (barrier_wait(me->start_barrier) != 0)
	// 	return (NULL);	// IDK yet
	// print_db(me, "passed the barrier");

	gettimeofday(&me->start_time, NULL);
	me->last_meal = me->start_time;
	if (me->initial_time_to_think_us)
		if (!philo_think(me, me->initial_time_to_think_us))
			return (NULL);
	while (true)
	{
		if (!philo_eat(me))
			break;
		if (!philo_sleep(me))
			break;
		if (!philo_think(me, me->time_to_think_us))
			break;
	}
	philo_release_forks(me);
	pthread_mutex_lock(&me->state_mutex);
	me->state = DEAD;
	pthread_mutex_unlock(&me->state_mutex);
	print_db(me, "has exited routine");
	return (NULL);
}
