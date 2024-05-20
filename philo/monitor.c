/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:55:06 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/20 18:37:11 by ldulling         ###   ########.fr       */
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
			if (philos[i].state != DEAD)
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

static void	broadcast_death(t_philo *philos, int number_of_philosophers, int i)
{
	struct timeval	death_time;
	int	j;

	gettimeofday(&death_time, NULL);
	j = (i + 1) % number_of_philosophers;
	while (j != i)
	{
		pthread_mutex_lock(&philos[j].state_mutex);
		philos[j].state = DYING;
		pthread_mutex_unlock(&philos[j].state_mutex);
		j = (j + 1) % number_of_philosophers;
	}
}

void	monitor(t_philo *philos, t_rules rules)
{
	int	number_of_philosophers;
	int	i;

	number_of_philosophers = rules.number_of_philosophers;
	i = 0;
	while (true)
	{
		pthread_mutex_lock(&philos[i].state_mutex);
		if (philos[i].state != ALIVE)
		{
			pthread_mutex_unlock(&philos[i].state_mutex);
			broadcast_death(philos, number_of_philosophers, i);
			print_death(philos, number_of_philosophers, i);
			break ;
		}
		pthread_mutex_unlock(&philos[i].state_mutex);
		i = (i + 1) % number_of_philosophers;
	}
}
