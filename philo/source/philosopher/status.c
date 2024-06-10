/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:41:35 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 16:38:57 by ldulling         ###   ########.fr       */
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
	me->latest_timestamp = get_elapsed_time_ms(
			(struct timeval *)me->start_time);
	if (me->latest_timestamp - me->last_meal_timestamp
		> (unsigned long long)me->rules->time_to_die_ms)
	{
		pthread_mutex_lock(me->state_mutex);
		me->state |= (DEAD | CONFIRMED);
		pthread_mutex_unlock(me->state_mutex);
		print_verbose_death(me);
		return (false);
	}
	return (true);
}
