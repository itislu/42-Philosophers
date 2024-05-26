/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:55:06 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/26 21:39:59 by ldulling         ###   ########.fr       */
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
			pthread_mutex_lock(&philos[i].state_mutex);
			state |= philos[i].state;
			pthread_mutex_unlock(&philos[i].state_mutex);
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

static void	broadcast_death(t_philo *philos, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_lock(&philos[i].state_mutex);
		philos[i].state |= DEAD;
		pthread_mutex_unlock(&philos[i].state_mutex);
		i++;
	}
}

void	monitor(t_philo *philos, t_rules rules)
{
	int		number_of_philosophers;
	int		i;
	t_state	state;

	number_of_philosophers = rules.number_of_philosophers;
	while (true)
	{
		i = 0;
		state = ALIVE;
		while (i < number_of_philosophers)
		{
			pthread_mutex_lock(&philos[i].state_mutex);
			state |= philos[i].state;
			pthread_mutex_unlock(&philos[i].state_mutex);
			if (state & DEAD)
			{
				broadcast_death(philos, number_of_philosophers);
				print_death(philos, number_of_philosophers, i);
				return ;
			}
			i++;
		}
		if (state & FULL)
		{
			dprintf(2, "FUUUUUUUUUUUUUUUUUUUUUUUULLLLLLLLLLLLLLLLLLL\n");
			break ;
		}
	}
}
