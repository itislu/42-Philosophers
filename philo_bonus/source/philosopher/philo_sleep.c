/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:19:42 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/05 11:07:30 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

bool	philo_sleep(t_philo *me)
{
	if (!print_if_alive(me, MSG_SLEEP))
		return (false);
	if (!usleep_while_alive_precise(me->rules->time_to_sleep_ms * 1000ULL, me))
		return (false);
	increase_target_time(
		&me->target_time, me->rules->time_to_sleep_ms * 1000ULL);
	return (true);
}
