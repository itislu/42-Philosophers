/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:20:12 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 16:48:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

static bool	iter_init_mutexes(pthread_mutex_t **mutexes_member, int count);
static void	iter_destroy_mutexes(pthread_mutex_t **mutexes_member, int count);

bool	init_mutexes(t_mutexes *mutexes, int count)
{
	memset(mutexes, 0, sizeof(t_mutexes));
	if (!iter_init_mutexes(&mutexes->forks, count))
		return (destroy_mutexes(mutexes, count), false);
	if (!iter_init_mutexes(&mutexes->state_mutexes, count))
		return (destroy_mutexes(mutexes, count), false);
	if (!iter_init_mutexes(&mutexes->sync_mutex, 1))
		return (destroy_mutexes(mutexes, count), false);
	if (!iter_init_mutexes(&mutexes->print_mutex, 1))
		return (destroy_mutexes(mutexes, count), false);
	return (true);
}

static bool	iter_init_mutexes(pthread_mutex_t **mutexes_member, int count)
{
	int	i;

	*mutexes_member = malloc(count * sizeof(pthread_mutex_t));
	if (!*mutexes_member)
		return (false);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&(*mutexes_member)[i], NULL) != 0)
		{
			iter_destroy_mutexes(mutexes_member, i);
			return (false);
		}
		i++;
	}
	return (true);
}

void	destroy_mutexes(t_mutexes *mutexes, int count)
{
	if (mutexes->forks)
		iter_destroy_mutexes(&mutexes->forks, count);
	if (mutexes->state_mutexes)
		iter_destroy_mutexes(&mutexes->state_mutexes, count);
	if (mutexes->sync_mutex)
		iter_destroy_mutexes(&mutexes->sync_mutex, 1);
	if (mutexes->print_mutex)
		iter_destroy_mutexes(&mutexes->print_mutex, 1);
}

static void	iter_destroy_mutexes(pthread_mutex_t **mutexes_member, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&(*mutexes_member)[i]);
		i++;
	}
	ft_free_and_null((void **)mutexes_member);
}
