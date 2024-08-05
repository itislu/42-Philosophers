/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:19:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/05 22:29:56 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

bool	philo_think_initial(t_philo *me)
{
	if (!print_if_alive(me, MSG_THINK))
		return (false);
	increase_target_time(&me->target_time, me->initial_think_time_us);
	if (!usleep_while_alive_precise_target(&me->target_time, me))
		return (false);
	return (true);
}

bool	philo_think(t_philo *me)
{
	unsigned long long	think_time_us;

	if (!print_if_alive(me, MSG_THINK))
		return (false);
	if (me->is_full)
		think_time_us = me->rules->time_to_die_ms * 1000ULL;
	else
		think_time_us = me->think_time_us;
	if (think_time_us)
	{
		increase_target_time(&me->target_time, think_time_us);
		if (!usleep_while_alive_precise_target(&me->target_time, me))
			return (false);
		increase_target_time(&me->target_time, MARGIN_MS / 2 * 1000);
	}
	return (true);
}
