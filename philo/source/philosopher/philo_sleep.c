/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:19:42 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 10:44:15 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "priv_philo.h"
#include "macros.h"
#include "typedefs.h"
#include <stdbool.h>

bool	philo_sleep(t_philo *me)
{
	if (!print_if_alive(me, MSG_SLEEP))
		return (false);
	usleep_while_alive_precise(me->rules->time_to_sleep_ms * 1000U, me);
	return (true);
}
