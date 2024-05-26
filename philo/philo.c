/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:54:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/26 16:36:11 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_alive(t_philo *me)
{
	pthread_mutex_lock(&me->state_mutex);
	if (me->state & (DYING | DEAD))
	{
		pthread_mutex_unlock(&me->state_mutex);
		return (false);
	}
	pthread_mutex_unlock(&me->state_mutex);
	me->latest_timestamp = get_elapsed_time_ms(me->start_time);
	if (me->latest_timestamp - me->last_meal_timestamp > (unsigned long long)me->rules->time_to_die_ms)
	{
		pthread_mutex_lock(&me->state_mutex);
		me->state |= DYING;
		pthread_mutex_unlock(&me->state_mutex);
		print_db_death(me);
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
	usleep_while_alive(me->rules->time_to_eat_ms * 1000U, me);

	me->release_forks(me);
	print_db(me, "has released forks");
	if (me->meals_remaining > 0)
	{
		if (--me->meals_remaining == 0)
		{
			pthread_mutex_lock(&me->state_mutex);
			me->state |= FULL;
			pthread_mutex_unlock(&me->state_mutex);
			print_db(me, "got full");
			usleep(100);
		}
	}
	return (true);
}

static bool	philo_sleep(t_philo *me)
{
	if (!print_if_alive(me, DFLT_PRINT_DELAY_US, MSG_SLEEP))
		return (false);
	usleep_while_alive(me->rules->time_to_sleep_ms * 1000U, me);
	return (true);
}

static bool	philo_think(t_philo *me, useconds_t time_to_think_us)
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
	pthread_mutex_lock(me->start_mutex);
	pthread_mutex_unlock(me->start_mutex);

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
	me->release_forks(me);
	pthread_mutex_lock(&me->state_mutex);
	me->state |= DEAD;
	pthread_mutex_unlock(&me->state_mutex);
	print_db(me, "has exited routine");
	return (NULL);
}
