/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:55:06 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 05:44:23 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "broadcast_death.h"

static t_state	monitor_cycle(t_philo *philos, int number_of_philosophers)
				__attribute__((always_inline));

void	monitor(t_philo *philos, t_rules rules)
{
	t_state	state;

	while (true)
	{
		state = monitor_cycle(philos, rules.number_of_philosophers);
		if (state & (DEAD | FULL))
			return ;
		usleep(MONITOR_INTERVAL_US);
	}
}

static __attribute__((always_inline))
t_state	monitor_cycle(t_philo *philos, int number_of_philosophers)
{
	int		i;
	t_state	state;

	i = 0;
	state = ~0;
	while (i < number_of_philosophers)
	{
		state |= DEAD;
		pthread_mutex_lock(philos[i].state_mutex);
		state &= philos[i].state;
		pthread_mutex_unlock(philos[i].state_mutex);
		if (state & DEAD)
		{
			broadcast_death(philos, number_of_philosophers);
			print_death(philos, number_of_philosophers, i);
			break ;
		}
		i++;
	}
	return (state);
}
