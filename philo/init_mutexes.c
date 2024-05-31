/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:20:12 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/31 21:17:22 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	iter_init_mutexes(pthread_mutex_t *mutexes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&mutexes[i], NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

bool	init_mutexes(t_mutexes *mutexes, t_rules *rules)
{
	memset(mutexes, 0, sizeof(t_mutexes));
	mutexes->forks = malloc(rules->number_of_philosophers * sizeof(pthread_mutex_t));
	if (!mutexes->forks)
		return (false);
	mutexes->state_mutexes = malloc(rules->number_of_philosophers * sizeof(pthread_mutex_t));
	if (!mutexes->state_mutexes)
		return (destroy_mutexes(mutexes, rules), false);
	mutexes->sync_mutex = malloc(sizeof(pthread_mutex_t));
	if (!mutexes->sync_mutex)
		return (destroy_mutexes(mutexes, rules), false);
	if (!iter_init_mutexes(mutexes->forks, rules->number_of_philosophers))
		return (destroy_mutexes(mutexes, rules), false);
	if (!iter_init_mutexes(mutexes->state_mutexes, rules->number_of_philosophers))
		return (destroy_mutexes(mutexes, rules), false);
	if (pthread_mutex_init(mutexes->sync_mutex, NULL) != 0)
		return (destroy_mutexes(mutexes, rules), false);
	return (true);
}

static void	iter_destroy_mutexes(pthread_mutex_t *mutexes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
}

void	destroy_mutexes(t_mutexes *mutexes, t_rules *rules)
{
	if (mutexes->forks)
	{
		iter_destroy_mutexes(mutexes->forks, rules->number_of_philosophers);
		free(mutexes->forks);
	}
	if (mutexes->state_mutexes)
	{
		iter_destroy_mutexes(mutexes->state_mutexes, rules->number_of_philosophers);
		free(mutexes->state_mutexes);
	}
	if (mutexes->sync_mutex)
	{
		pthread_mutex_destroy(mutexes->sync_mutex);
		free(mutexes->sync_mutex);
	}
}
