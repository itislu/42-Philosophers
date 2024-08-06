/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:19:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/07 01:45:10 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

bool	philo_think_initial(t_philo *me)
{
	if (!print_if_alive(me, MSG_THINK))
		return (false);
	increase_target_time(&me->cycle_target_time, me->initial_think_time_us);
	if (!usleep_while_alive_precise_target(&me->cycle_target_time, me))
		return (false);
	return (true);
}

bool	philo_think(t_philo *me)
{
	if (!print_if_alive(me, MSG_THINK))
		return (false);
	if (me->think_time_us)
	{
		if (!usleep_while_alive_precise_target(&me->cycle_target_time, me))
			return (false);
		increase_target_time(&me->cycle_target_time, me->cycle_time_us);
	}
	return (true);
}
