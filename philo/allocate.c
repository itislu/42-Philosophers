/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:22:13 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/19 22:27:44 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	allocate_memory(pthread_mutex_t **forks, t_philo **philos, const t_rules *rules)
{
	*forks = malloc(sizeof(pthread_mutex_t) * rules->number_of_philosophers);
	if (!*forks)
		return (false);
	*philos = malloc(sizeof(t_philo) * rules->number_of_philosophers);
	if (!*philos)
	{
		free(*forks);
		return (false);
	}
	return (true);
}

void	clean(t_philo *philos, pthread_mutex_t *forks, const t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].is_dead_mutex);
		i++;
	}
	free(forks);
	free(philos);
}
