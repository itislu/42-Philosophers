/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:41:35 by ldulling          #+#    #+#             */
/*   Updated: 2024/07/31 18:36:20 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

bool	check_alive(t_philo *me)
{
	if (get_is_stopped(me))
		return (false);
	me->latest_timestamp_ms = get_elapsed_time_ms(me->start_time);
	if (me->latest_timestamp_ms - me->last_meal_timestamp_ms
		> (unsigned long long)me->rules->time_to_die_ms)
	{
		sem_post(me->semaphores->dead.sem);
		me->is_dead = true;
		if (VERBOSE)
			print_verbose_death(me);
		return (false);
	}
	return (true);
}

void	set_is_stopped(t_philo *me)
{
	sem_wait(me->semaphores->philo_mutex.sem);
	me->is_stopped = true;
	sem_post(me->semaphores->philo_mutex.sem);
}

bool	get_is_stopped(t_philo *me)
{
	bool	is_stopped;

	sem_wait(me->semaphores->philo_mutex.sem);
	is_stopped = me->is_stopped;
	sem_post(me->semaphores->philo_mutex.sem);
	return (is_stopped);
}
