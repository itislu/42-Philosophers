/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 00:56:07 by ldulling          #+#    #+#             */
/*   Updated: 2024/07/30 00:56:07 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

void	init_monitor(
			t_mon *monitor,
			t_philo *philos,
			t_semaphores *semaphores,
			t_rules *rules)
{
	memset(monitor, 0, sizeof(t_mon));
	monitor->philos = philos;
	monitor->semaphores = semaphores;
	monitor->rules = rules;
}
