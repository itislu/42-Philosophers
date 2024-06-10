/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:19:42 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 16:38:57 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

bool	philo_sleep(t_philo *me)
{
	if (!print_if_alive(me, MSG_SLEEP))
		return (false);
	usleep_while_alive_precise(me->rules->time_to_sleep_ms * 1000U, me);
	return (true);
}
