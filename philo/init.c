/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:16:53 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/20 00:56:14 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

bool	init_forks(pthread_mutex_t *forks, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

static bool	init_is_dead_mutexes(t_philo *philos, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_mutex_init(&philos[i].is_dead_mutex, NULL) != 0)
			break;
		i++;
	}
	if (i < number_of_philosophers)
	{
		while (i >= 0)
		{
			pthread_mutex_destroy(&philos[i].is_dead_mutex);
			i--;
		}
		return (false);
	}
	return (true);
}

static useconds_t	calc_even(const t_rules *rules, int i)
{
	(void)rules;
	if (i % 2 == 0)
		return (0);
	else
		return (10 * 1000);
}

static useconds_t	calc_odd(const t_rules *rules, int i)
{
	(void)rules;
	if (i % 2 == 0)
		return (0);
	else
		return (10 * 1000);
}

useconds_t	calc_initial_think(const t_rules *rules, int i)
{
	if (rules->number_of_philosophers % 2 == 0)
		return (calc_even(rules, i));
	else
	 	return (calc_odd(rules, i));
}

bool	init_philos(t_philo *philos, pthread_mutex_t *forks, const t_rules *rules, t_barrier *start_barrier)
{
	int	i;

	if (barrier_init(start_barrier, rules->number_of_philosophers) != 0)
		return (false);
	if (!init_is_dead_mutexes(philos, rules->number_of_philosophers))
		return (false);
	i = 0;
	while (i < rules->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % rules->number_of_philosophers];
		philos[i].is_dead = false;
		philos[i].initial_think_us = calc_initial_think(rules, i);
		philos[i].rules = rules;
		philos[i].start_barrier = start_barrier;
		i++;
	}
	return (true);
}
