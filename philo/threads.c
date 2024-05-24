/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:51:10 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/24 23:44:22 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	create_philo_threads(t_philo *philos, const t_rules *rules)
{
	int	i;
	int	number_of_philosophers;

	number_of_philosophers = rules->number_of_philosophers;
	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_create(&philos[i].thread, NULL, &philosopher, &philos[i]) != 0)
			return (false);
		i++;
	}
	return (true);
}

void	join_philo_threads(t_philo *philos, const t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philosophers)
	{
		// print_db(&philos[i], "will be joined");
		pthread_join(philos[i].thread, NULL);
		// print_db(&philos[i], "has been joined");
		i++;
	}
}
