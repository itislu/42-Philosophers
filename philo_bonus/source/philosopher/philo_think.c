/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:19:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/02 18:27:56 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

static inline unsigned long long	calc_think_us(
										t_philo *me,
										unsigned long long think_time_us)
									__attribute__((always_inline));
static inline unsigned long long	calc_think_odd_us(t_philo *me)
									__attribute__((always_inline));

bool	philo_think_initial(t_philo *me)
{
	if (!print_if_alive(me, MSG_THINK))
		return (false);
	if (!usleep_while_alive(me->initial_think_time_us, me))
		return (false);
	return (true);
}

bool	philo_think(t_philo *me)
{
	unsigned long long	think_time_us;

	if (!print_if_alive(me, MSG_THINK))
		return (false);
	think_time_us = calc_think_us(me, me->think_time_us);
	if (think_time_us)
		if (!usleep_while_alive(think_time_us, me))
			return (false);
	return (true);
}

static inline __attribute__((always_inline))
unsigned long long	calc_think_us(
						t_philo *me,
						unsigned long long think_time_us)
{
	if (me->rules->num_of_philos % 2 == 1)
		return (calc_think_odd_us(me));
	else
		return (think_time_us);
}

static inline __attribute__((always_inline))
unsigned long long	calc_think_odd_us(t_philo *me)
{
	long long	think_time_ms;

	if ((me->meals_eaten - 1) % (me->rules->num_of_philos / 2)
		== (me->id - 1 - (me->id == me->rules->num_of_philos))
		/ 2ULL)
	{
		me->is_outsider = true;
		think_time_ms = me->rules->time_to_eat_ms * 2LL
			- me->rules->time_to_sleep_ms;
	}
	else
	{
		me->is_outsider = false;
		think_time_ms = me->rules->time_to_eat_ms
			- me->rules->time_to_sleep_ms;
	}
	if (think_time_ms > MARGIN_MS / 2)
		return ((think_time_ms - MARGIN_MS / 2) * 1000ULL);
	else
		return (0);
}
