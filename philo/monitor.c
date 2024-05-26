/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:55:06 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/26 18:13:00 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_all_dead(t_philo *philos, int number_of_philosophers)
{
	int		i;
	bool	all_dead;

	while (true)
	{
		i = 0;
		all_dead = true;
		while (i < number_of_philosophers)
		{
			pthread_mutex_lock(&philos[i].state_mutex);
			if (!(philos[i].state & DEAD))
				all_dead = false;
			pthread_mutex_unlock(&philos[i].state_mutex);
			i++;
		}
		if (all_dead)
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
		philos[i].state |= DYING;
		pthread_mutex_unlock(&philos[i].state_mutex);
		i++;
	}
}

void	monitor(t_philo *philos, t_rules rules)
{
	int	number_of_philosophers;
	int	i;
	bool	all_full;

	number_of_philosophers = rules.number_of_philosophers;
	while (true)
	{
		i = 0;
		all_full = true;
		while (i < number_of_philosophers)
		{
			pthread_mutex_lock(&philos[i].state_mutex);
			if (philos[i].state & DEAD)
			{
				pthread_mutex_unlock(&philos[i].state_mutex);
				broadcast_death(philos, number_of_philosophers);
				print_death(philos, number_of_philosophers, i);
				return ;
			}
			else if (!(philos[i].state & FULL))
			{
				pthread_mutex_unlock(&philos[i].state_mutex);
				all_full = false;
			}
			else
				pthread_mutex_unlock(&philos[i].state_mutex);
			i++;
		}
		if (all_full)
		{
			dprintf(2, "FUUUUUUUUUUUUUUUUUUUUUUUULLLLLLLLLLLLLLLLLLL\n");
			break ;
		}
	}
}
