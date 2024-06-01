/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:54:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/02 00:24:11 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_alive(t_philo *me)
{
	pthread_mutex_lock(&me->state_mutex);
	if (me->state & DEAD)
	{
		me->state |= CONFIRMED;
		pthread_mutex_unlock(&me->state_mutex);
		return (false);
	}
	pthread_mutex_unlock(&me->state_mutex);
	me->latest_timestamp = get_elapsed_time_ms((struct timeval *)me->start_time);
	if (me->latest_timestamp - me->last_meal_timestamp > (unsigned long long)me->rules->time_to_die_ms)
	{
		pthread_mutex_lock(&me->state_mutex);
		me->state |= (DEAD | CONFIRMED);
		pthread_mutex_unlock(&me->state_mutex);
		print_verbose_death(me);
		return (false);
	}
	return (true);
}

static bool	philo_eat(t_philo *me)
{
	if (!me->take_forks(me))
		return (false);

	if (!print_if_alive(me, DFLT_PRINT_DELAY_US, MSG_EAT))
		return (false);
	me->last_meal_timestamp = me->latest_timestamp;
	usleep_while_alive_precise(me->rules->time_to_eat_ms * 1000U, me);

	me->release_forks(me);
	print_verbose(me, "has released forks");
	me->meals_eaten++;
	if (me->rules->number_of_times_each_philosopher_must_eat > 0
		&& (int)me->meals_eaten == me->rules->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&me->state_mutex);
		me->state |= FULL;
		pthread_mutex_unlock(&me->state_mutex);
		print_verbose(me, "got full");
		return (false);
	}
	return (true);
}

static bool	philo_sleep(t_philo *me)
{
	if (!print_if_alive(me, DFLT_PRINT_DELAY_US, MSG_SLEEP))
		return (false);
	usleep_while_alive_precise(me->rules->time_to_sleep_ms * 1000U, me);
	return (true);
}

static useconds_t	calc_think_us(t_philo *me, useconds_t time_to_think_us)
{
	if (me->rules->number_of_philosophers % 2 == 1)
	{
		if ((me->meals_eaten - 1) % (me->rules->number_of_philosophers / 2) == (me->id - 1) / 2
			|| (me->id == me->rules->number_of_philosophers && (me->meals_eaten - 1) % (me->rules->number_of_philosophers / 2) == (me->id - 2) / 2))
			return ((me->rules->time_to_eat_ms * 2 - me->rules->time_to_sleep_ms - MARGIN_MS / 2) * 1000U);
		else if (me->rules->time_to_eat_ms - me->rules->time_to_sleep_ms > MARGIN_MS / 2)
			return ((me->rules->time_to_eat_ms - me->rules->time_to_sleep_ms - MARGIN_MS / 2) * 1000U);
		else
			return (0);
	}
	else
		return (time_to_think_us);
}

static bool	philo_think(t_philo *me, useconds_t time_to_think_us)
{
	if (!print_if_alive(me, DFLT_PRINT_DELAY_US, MSG_THINK))
		return (false);
	time_to_think_us = calc_think_us(me, time_to_think_us);
	if (time_to_think_us)
		usleep_while_alive(time_to_think_us, me);
	return (true);
}

static bool	philo_think_initial(t_philo *me, useconds_t time_to_think_us)
{
	if (!print_if_alive(me, DFLT_PRINT_DELAY_US, MSG_THINK))
		return (false);
	if (time_to_think_us)
		usleep_while_alive(time_to_think_us, me);
	return (true);
}

// Need a value in the philo struct that tell me how long to think in the beginning
void	*philosopher(void *arg)
{
	t_philo			*me;

	me = (t_philo *)arg;
	pthread_mutex_lock(me->sync_mutex);
	pthread_mutex_unlock(me->sync_mutex);

	if (me->initial_time_to_think_us)
		if (!philo_think_initial(me, me->initial_time_to_think_us))
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
	me->release_forks(me);
	print_verbose(me, "has exited routine");
	return (NULL);
}
