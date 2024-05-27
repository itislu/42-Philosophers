/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:22:13 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/27 00:08:10 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	allocate_memory(pthread_mutex_t **forks, t_philo **philos, const t_rules *rules)
{
	*forks = malloc(rules->number_of_philosophers * sizeof(pthread_mutex_t));
	if (!*forks)
		return (false);
	*philos = malloc(rules->number_of_philosophers * sizeof(t_philo));
	if (!*philos)
	{
		free(*forks);
		return (false);
	}
	memset(*philos, 0, rules->number_of_philosophers * sizeof(t_philo));
	return (true);
}

void	free_memory(pthread_mutex_t *forks, t_philo *philos)
{
	free(forks);
	free(philos);
}

void	clean(t_philo *philos, pthread_mutex_t *forks, const t_rules *rules, pthread_mutex_t *sync_mutex)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(sync_mutex);
	free_memory(forks, philos);
}
