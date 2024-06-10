/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:51:10 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/02 00:24:11 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	create_philo_threads(t_philo *philos, const t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philosophers)
	{
		if (pthread_create(&philos[i].thread, NULL, &philosopher, &philos[i]) != 0)
		{
			broadcast_death(philos, i);
			pthread_mutex_unlock(philos[i].sync_mutex);
			join_philo_threads(philos, i);
			return (false);
		}
		i++;
	}
	return (true);
}

void	join_philo_threads(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		print_verbose(&philos[i], "will be joined");
		pthread_join(philos[i].thread, NULL);
		print_verbose(&philos[i], "has been joined");
		i++;
	}
}
