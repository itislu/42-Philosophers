/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:41:35 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/11 10:38:14 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

bool	check_alive(t_philo *me)
{
	pthread_mutex_lock(me->state_mutex);
	if (me->state & DEAD)
	{
		me->state |= CONFIRMED;
		pthread_mutex_unlock(me->state_mutex);
		return (false);
	}
	pthread_mutex_unlock(me->state_mutex);
	me->latest_timestamp_us = get_elapsed_time_us(
			(struct timeval *)me->start_time);
	if (me->latest_timestamp_us - me->last_meal_timestamp_us
		> (unsigned long long)me->rules->time_to_die_us)
	{
		pthread_mutex_lock(me->state_mutex);
		me->state |= (DEAD | CONFIRMED);
		pthread_mutex_unlock(me->state_mutex);
		if (VERBOSE)
			print_verbose_death(me);
		return (false);
	}
	return (true);
}
