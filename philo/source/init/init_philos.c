/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:16:53 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 13:47:05 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

static void	set_forks(
				t_philo *philos,
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
		(*philos)[i].id = i + 1;
		(*philos)[i].start_time = start_time;
		(*philos)[i].state = ALIVE;
		(*philos)[i].state_mutex = &mutexes->state_mutexes[i];
		(*philos)[i].sync_mutex = mutexes->sync_mutex;
		(*philos)[i].print_mutex = mutexes->print_mutex;
		set_forks(*philos, mutexes->forks, rules, i);
		(*philos)[i].is_outsider = is_outsider(rules, (*philos)[i].id);
		(*philos)[i].initial_thinking_time_us = calc_initial_think_us(
				rules, (*philos)[i].id);
		(*philos)[i].thinking_time_us = calc_thinking_time_us(
				rules, (*philos)[i].id);
		(*philos)[i].rules = rules;
		i++;
	}
	return (true);
}

static void	set_forks(
				t_philo *philos,
				pthread_mutex_t *forks,
				const t_rules *rules,
				int i)
{
	philos[i].left_fork = &forks[i];
	philos[i].right_fork = &forks[(i + 1) % rules->num_of_philos];
	if (i % 2 == 0)
	{
		philos[i].take_forks = &take_forks_left_first;
		philos[i].release_forks = &release_forks_left_first;
	}
	else
	{
		philos[i].take_forks = &take_forks_right_first;
		philos[i].release_forks = &release_forks_right_first;
	}
}
