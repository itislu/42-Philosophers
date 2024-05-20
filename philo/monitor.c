/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:55:06 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/20 11:40:07 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	broadcast_death(t_philo *philos, int number_of_philosophers, int i)
{
	int	j;

	j = (i + 1) % number_of_philosophers;
	while (j != i)
	{
		pthread_mutex_lock(&philos[j].is_dead_mutex);
		philos[j].is_dead = true;
		pthread_mutex_unlock(&philos[j].is_dead_mutex);
		j = (j + 1) % number_of_philosophers;
	}
}

void	monitor(t_philo *philos, t_rules rules)
{
	int	number_of_philosophers;
	int	i;

	number_of_philosophers = rules.number_of_philosophers;
	while (1)
	{
		i = 0;
		while (i < number_of_philosophers)
		{
			// usleep(100);
			pthread_mutex_lock(&philos[i].is_dead_mutex);
			if (philos[i].is_dead)
			{
				pthread_mutex_unlock(&philos[i].is_dead_mutex);
				broadcast_death(philos, number_of_philosophers, i);
				break ;
			}
			pthread_mutex_unlock(&philos[i].is_dead_mutex);
			i++;
		}
	}
}
