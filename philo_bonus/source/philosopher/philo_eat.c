/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:19:02 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/11 10:38:14 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

bool	philo_eat(t_philo *me)
{
	if (!take_forks(me))
		return (false);
	if (!print_if_alive(me, MSG_EAT))
		return (false);
	me->last_meal_timestamp_ms = me->latest_timestamp_ms;
	if (!usleep_while_alive_precise(me->rules->time_to_eat_ms * 1000ULL, me))
		return (false);
	release_forks(me);
	me->meals_eaten++;
	if (me->rules->num_each_philo_must_eat > 0
		&& (int)me->meals_eaten == me->rules->num_each_philo_must_eat)
	{
		sem_post(me->semaphores->full.sem);
		me->is_full = true;
		if (VERBOSE)
			print_verbose(me, "got full");
		// I did this in mand so the simulation is technically running still and everyone can die.
		usleep_while_alive(me->rules->time_to_die_ms * 1000ULL, me);
		return (false);
	}
	return (true);
}
