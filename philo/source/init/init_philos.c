/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:16:53 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/06 01:26:48 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

static void	init_philo(
				t_philo *philo,
				t_mutexes *mutexes,
				const t_rules *rules,
				struct timeval *start_time);
static void	set_forks(
				t_philo *philo,
				pthread_mutex_t *forks,
				const t_rules *rules,
				int i);

bool	init_philos(
			t_philo **philos,
			t_mutexes *mutexes,
			const t_rules *rules,
			struct timeval *start_time)
{
	int	i;

	*philos = malloc(rules->num_of_philos * sizeof(t_philo));
	if (!*philos)
		return (false);
	memset(*philos, 0, rules->num_of_philos * sizeof(t_philo));
	i = 0;
	while (i < rules->num_of_philos)
	{
		init_philo(&(*philos)[i], mutexes, rules, start_time);
		i++;
	}
	return (true);
}

static void	init_philo(
				t_philo *philo,
				t_mutexes *mutexes,
				const t_rules *rules,
				struct timeval *start_time)
{
	static int	i = 0;

	philo->id = i + 1;
	philo->start_time = start_time;
	philo->rules = rules;
	philo->state = ALIVE;
	philo->state_mutex = &mutexes->state_mutexes[i];
	philo->sync_mutex = mutexes->sync_mutex;
	philo->print_mutex = mutexes->print_mutex;
	set_forks(philo, mutexes->forks, rules, i);
	philo->initial_think_time_us = calc_initial_think_time_us(rules, philo->id);
	philo->think_time_us = calc_think_time_us(rules);
	philo->initial_cycle_time_us = calc_initial_cycle_time_us(rules, philo);
	philo->cycle_time_us = calc_cycle_time_us(rules, philo);
	i++;
}

static void	set_forks(
				t_philo *philo,
				pthread_mutex_t *forks,
				const t_rules *rules,
				int i)
{
	philo->left_fork = &forks[i];
	philo->right_fork = &forks[(i + 1) % rules->num_of_philos];
	if (ft_iseven(i))
	{
		philo->take_forks = &take_forks_left_first;
		philo->release_forks = &release_forks_left_first;
	}
	else
	{
		philo->take_forks = &take_forks_right_first;
		philo->release_forks = &release_forks_right_first;
	}
}
