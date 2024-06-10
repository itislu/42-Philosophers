/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:19:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 02:20:29 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static __attribute__((always_inline))
useconds_t	calc_think_us(t_philo *me, useconds_t time_to_think_us)
{
	int	time_to_think_ms;

	if (me->rules->number_of_philosophers % 2 == 1)
	{
		if ((me->meals_eaten - 1) % (me->rules->number_of_philosophers / 2) == (me->id - 1 - (me->id == me->rules->number_of_philosophers)) / 2ULL)
		{
			me->is_outsider = true;
			time_to_think_ms = me->rules->time_to_eat_ms * 2 - me->rules->time_to_sleep_ms;
		}
		else
		{
			me->is_outsider = false;
			time_to_think_ms = me->rules->time_to_eat_ms - me->rules->time_to_sleep_ms;
		}
		if (time_to_think_ms > MARGIN_MS / 2)
			return ((time_to_think_ms - MARGIN_MS / 2) * 1000U);
		else
			return (0);
	}
	else
		return (time_to_think_us);
}

bool	philo_think(t_philo *me, useconds_t time_to_think_us)
{
	if (!print_if_alive(me, MSG_THINK))
		return (false);
	time_to_think_us = calc_think_us(me, time_to_think_us);
	if (time_to_think_us)
		usleep_while_alive(time_to_think_us, me);
	return (true);
}

bool	philo_think_initial(t_philo *me, useconds_t time_to_think_us)
{
	if (!print_if_alive(me, MSG_THINK))
		return (false);
	if (time_to_think_us)
		usleep_while_alive(time_to_think_us, me);
	return (true);
}
