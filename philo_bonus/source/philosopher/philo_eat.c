/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:19:02 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/06 01:31:09 by ldulling         ###   ########.fr       */
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
	if (me->rules->num_each_philo_must_eat > 0 && me->meals_eaten
		== (unsigned long long)me->rules->num_each_philo_must_eat)
	{
		sem_post(me->semaphores->full.sem);
		if (VERBOSE)
			print_verbose(me, "got full");
		me->is_full = true;
	}
	return (true);
}
