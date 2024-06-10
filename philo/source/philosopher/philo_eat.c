/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:19:02 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 02:20:00 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_eat(t_philo *me)
{
	if (!me->take_forks(me))
		return (false);

	if (!print_if_alive(me, MSG_EAT))
		return (false);
	me->last_meal_timestamp = me->latest_timestamp;
	usleep_while_alive_precise(me->rules->time_to_eat_ms * 1000U, me);

	me->release_forks(me);
	print_verbose(me, "has released forks");
	me->meals_eaten++;
	if (me->rules->number_of_times_each_philosopher_must_eat > 0
		&& (int)me->meals_eaten == me->rules->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(me->state_mutex);
		me->state |= FULL;
		pthread_mutex_unlock(me->state_mutex);
		print_verbose(me, "got full");
		return (false);
	}
	return (true);
}
