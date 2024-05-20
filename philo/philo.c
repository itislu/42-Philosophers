/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:54:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/20 13:16:30 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_db_death(t_philo *me)
{
	if (me->id % 2 == 1)
		dprintf(2, SPACING "%d DIED %llu MS AFTER LAST MEAL" STY_RES "\n", me->id, get_timestamp_ms(me->last_meal));
	else
		dprintf(2, "%d DIED %llu MS AFTER LAST MEAL\n", me->id, get_timestamp_ms(me->last_meal));
}

void	print_db(t_philo *me, const char *msg)
{
	if (me->id % 2 == 1)
		dprintf(2, SPACING "%llu %d %s" STY_RES "\n", get_timestamp_ms(me->start_time), me->id, msg);
	else
		dprintf(2, "%llu %d %s\n", get_timestamp_ms(me->start_time), me->id, msg);
}

void	print_msg(t_philo *me, const char *msg)
{
	char	buffer[256];

	snprintf(buffer, 256, msg, get_timestamp_ms(me->start_time), me->id);
	if (me->id % 2 == 1)
		printf(SPACING "%s", buffer);
	else
	 	printf("%s", buffer);
}

bool	check_alive(t_philo *me)
{
	print_db(me, "is checking if alive");
	pthread_mutex_lock(&me->is_dead_mutex);
	if (me->is_dead)
	{
		pthread_mutex_unlock(&me->is_dead_mutex);
		return (false);
	}
	if (get_timestamp_ms(me->last_meal) > (unsigned long long)me->rules->time_to_die_ms)
	{
		me->is_dead = true;
		pthread_mutex_unlock(&me->is_dead_mutex);
		usleep(1000);
		print_msg(me, MSG_DEAD);
		print_db_death(me);
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
	print_msg(me, msg);
	return (true);
}

static void	philo_release_forks(t_philo *me)
{
	pthread_mutex_unlock(me->left_fork);
	pthread_mutex_unlock(me->right_fork);
}

static bool	philo_take_fork(t_philo *me, pthread_mutex_t *fork)
{
	if (pthread_mutex_lock(fork) != 0)
		return (false);
	// dprintf(2, "%llu %d has locked fork\n", get_timestamp_ms(me->start_time), me->id);
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
	print_db(me, "has taken left fork");
	if (!philo_take_fork(me, me->right_fork))
	{
		pthread_mutex_unlock(me->left_fork);
		return (false);
	}
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
	usleep(me->rules->time_to_eat_ms * 1000);
	philo_release_forks(me);
	print_db(me, "has released forks");
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

	gettimeofday(&me->start_time, NULL);
	print_db(me, "waits at barrier");

	if (barrier_wait(me->start_barrier) != 0)
		return (NULL);	// IDK yet

	print_db(me, "passed the barrier");

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
		if (!philo_think(me, 0))
			break;
	}
	return (NULL);
}
