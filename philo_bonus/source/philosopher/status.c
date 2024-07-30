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
	if (me->state & STOPPED)
		return (false);
	me->latest_timestamp_ms = get_elapsed_time_ms(me->start_time);
	if (me->latest_timestamp_ms - me->last_meal_timestamp_ms
		> (unsigned long long)me->rules->time_to_die_ms)
	{
		sem_post(me->semaphores->dead.sem);
		me->state |= DEAD;
		if (VERBOSE)
			print_verbose_death(me);
		return (false);
	}
	return (true);
}
