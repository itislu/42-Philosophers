/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:19:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 16:38:57 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

static unsigned int	calc_think_us(t_philo *me, unsigned int thinking_time_us)
					__attribute__((always_inline));

bool	philo_think(t_philo *me, unsigned int thinking_time_us)
{
	if (!print_if_alive(me, MSG_THINK))
		return (false);
	thinking_time_us = calc_think_us(me, thinking_time_us);
	if (thinking_time_us)
		usleep_while_alive(thinking_time_us, me);
	return (true);
}

bool	philo_think_initial(t_philo *me, unsigned int thinking_time_us)
{
	if (!print_if_alive(me, MSG_THINK))
		return (false);
	if (thinking_time_us)
		usleep_while_alive(thinking_time_us, me);
	return (true);
}

static __attribute__((always_inline))
unsigned int	calc_think_us(t_philo *me, unsigned int thinking_time_us)
{
	int	thinking_time_ms;

	if (me->rules->num_of_philos % 2 == 1)
	{
		if ((me->meals_eaten - 1) % (me->rules->num_of_philos / 2)
			== (me->id - 1 - (me->id == me->rules->num_of_philos)) / 2ULL)
		{
			me->is_outsider = true;
			thinking_time_ms = me->rules->time_to_eat_ms * 2
				- me->rules->time_to_sleep_ms;
		}
		else
		{
			me->is_outsider = false;
			thinking_time_ms = me->rules->time_to_eat_ms
				- me->rules->time_to_sleep_ms;
		}
		if (thinking_time_ms > MARGIN_MS / 2)
			return ((thinking_time_ms - MARGIN_MS / 2) * 1000U);
		else
			return (0);
	}
	else
		return (thinking_time_us);
}
