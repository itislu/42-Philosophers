/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:55:06 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 13:52:48 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor_priv.h"

static inline t_state	monitor_cycle(t_philo *philos, int num_of_philos)
						__attribute__((always_inline));

void	monitor(t_philo *philos, const t_rules *rules)
{
	t_state	state;

	while (true)
	{
		usleep(MONITOR_INTERVAL_US);
		state = monitor_cycle(philos, rules->num_of_philos);
		if (state & DEAD)
			return ;
		else if (state & FULL)
		{
			if (VERBOSE)
				print_verbose_monitor(philos, "All philosophers got full");
			broadcast_death(philos, rules->num_of_philos);
			return ;
		}
	}
}

static inline __attribute__((always_inline))
t_state	monitor_cycle(t_philo *philos, int num_of_philos)
{
	int		i;
	t_state	state;

	i = 0;
	state = ~0;
	while (i < num_of_philos)
	{
		state |= DEAD;
		pthread_mutex_lock(philos[i].state_mutex);
		state &= philos[i].state;
		pthread_mutex_unlock(philos[i].state_mutex);
		if (state & DEAD)
		{
			broadcast_death(philos, num_of_philos);
			print_death(philos, num_of_philos, i);
			break ;
		}
		i++;
	}
	return (state);
}
