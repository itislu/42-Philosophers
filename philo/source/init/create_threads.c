/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:51:10 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/03 18:38:26 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

bool	create_philo_threads(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_create(
				&philos[i].thread, NULL, &philosopher, &philos[i]) != 0)
		{
			broadcast(philos, STOPPED, i);
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
		if (VERBOSE)
			print_verbose(&philos[i], "will be joined");
		pthread_join(philos[i].thread, NULL);
		if (VERBOSE)
			print_verbose(&philos[i], "has been joined");
		i++;
	}
}
