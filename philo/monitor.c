/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:55:06 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/02 14:42:51 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_all_dead(t_philo *philos, int number_of_philosophers)
{
	int		i;
	t_state	state;

	while (true)
	{
		i = 0;
		state = ALIVE;
		while (i < number_of_philosophers)
		{
			pthread_mutex_lock(philos[i].state_mutex);
			state |= philos[i].state;
			pthread_mutex_unlock(philos[i].state_mutex);
			i++;
		}
		if (state & (DEAD | CONFIRMED))
			break ;
	}
}

static void	print_death(t_philo *philos, int number_of_philosophers, int dead_philo)
{
	wait_all_dead(philos, number_of_philosophers);
	print_msg(&philos[dead_philo], MSG_DEAD);
}

void	broadcast_death(t_philo *philos, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_lock(philos[i].state_mutex);
		philos[i].state |= DEAD;
		pthread_mutex_unlock(philos[i].state_mutex);
		i++;
	}
}

t_state	monitor_cycle(t_philo *philos, int number_of_philosophers)
{
	int		i;
	t_state	total_state;
	t_state	philo_state;

	total_state = ALIVE;
	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_lock(philos[i].state_mutex);
		philo_state = philos[i].state;
		pthread_mutex_unlock(philos[i].state_mutex);
		total_state = (total_state | philo_state) & (~FULL | philo_state);
		if (total_state & DEAD)
		{
			broadcast_death(philos, number_of_philosophers);
			print_death(philos, number_of_philosophers, i);
			return (total_state);
		}
		i++;
	}
	return (total_state);
}

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
