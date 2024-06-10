/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:20:12 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 13:47:25 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

static bool	iter_init_mutexes(pthread_mutex_t *mutexes, int count);
static void	iter_destroy_mutexes(pthread_mutex_t *mutexes, int count);

bool	init_mutexes(t_mutexes *mutexes, t_rules *rules)
{
	memset(mutexes, 0, sizeof(t_mutexes));
	mutexes->forks = malloc(rules->num_of_philos * sizeof(pthread_mutex_t));
	if (!mutexes->forks)
		return (false);
	mutexes->state_mutexes = malloc(
			rules->num_of_philos * sizeof(pthread_mutex_t));
	if (!mutexes->state_mutexes)
		return (destroy_mutexes(mutexes, rules), false);
	mutexes->sync_mutex = malloc(sizeof(pthread_mutex_t));
	if (!mutexes->sync_mutex)
		return (destroy_mutexes(mutexes, rules), false);
	mutexes->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!mutexes->print_mutex)
		return (destroy_mutexes(mutexes, rules), false);
	if (!iter_init_mutexes(mutexes->forks, rules->num_of_philos))
		return (destroy_mutexes(mutexes, rules), false);
	if (!iter_init_mutexes(mutexes->state_mutexes, rules->num_of_philos))
		return (destroy_mutexes(mutexes, rules), false);
	if (pthread_mutex_init(mutexes->sync_mutex, NULL) != 0)
		return (destroy_mutexes(mutexes, rules), false);
	if (pthread_mutex_init(mutexes->print_mutex, NULL) != 0)
		return (destroy_mutexes(mutexes, rules), false);
	return (true);
}

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

void	destroy_mutexes(t_mutexes *mutexes, t_rules *rules)
{
	if (mutexes->forks)
	{
		iter_destroy_mutexes(mutexes->forks, rules->num_of_philos);
		free(mutexes->forks);
	}
	if (mutexes->state_mutexes)
	{
		iter_destroy_mutexes(mutexes->state_mutexes, rules->num_of_philos);
		free(mutexes->state_mutexes);
	}
	if (mutexes->sync_mutex)
	{
		pthread_mutex_destroy(mutexes->sync_mutex);
		free(mutexes->sync_mutex);
	}
	if (mutexes->print_mutex)
	{
		pthread_mutex_destroy(mutexes->print_mutex);
		free(mutexes->print_mutex);
	}
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
