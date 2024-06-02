/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:16:53 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/02 16:28:48 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_outsider(const t_rules *rules, int id)
{
	if (rules->number_of_philosophers % 2 == 1
		&& rules->number_of_philosophers > 1
		&& id == rules->number_of_philosophers)
		return (true);
	return (false);
}

static useconds_t	calc_even_us(const t_rules *rules, int id)
{
	(void)rules;
	if (id % 2 == 0)
		return (MARGIN_MS / 2 * 1000);
	else
		return (0);
}

static useconds_t	calc_odd_us(const t_rules *rules, int id)
{
	if (is_outsider(rules, id))
		return ((rules->time_to_eat_ms * 2 - MARGIN_MS / 2) * 1000U);
	else if (id % 2 == 0)
		return (MARGIN_MS / 2 * 1000);
	else
		return (0);
}

useconds_t	calc_initial_think_us(const t_rules *rules, int id)
{
	if (rules->number_of_philosophers < 2)
		return (rules->time_to_die_us + 1000);
	else if (rules->number_of_philosophers % 2 == 0)
		return (calc_even_us(rules, id));
	else
		return (calc_odd_us(rules, id));
}

useconds_t	calc_time_to_think_us(const t_rules *rules, int id)
{
	(void)id;
	if (rules->time_to_eat_ms > rules->time_to_sleep_ms + MARGIN_MS / 2)
		return ((rules->time_to_eat_ms - rules->time_to_sleep_ms - MARGIN_MS / 2) * 1000U);
	else
		return (0);
}

static void	set_forks(t_philo *philos, pthread_mutex_t *forks, const t_rules *rules, int i)
{
	philos[i].left_fork = &forks[i];
	philos[i].right_fork = &forks[(i + 1) % rules->number_of_philosophers];
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

bool	init_philos(t_philo **philos, t_mutexes *mutexes, const t_rules *rules, struct timeval *start_time)
{
	int	i;

	*philos = malloc(rules->number_of_philosophers * sizeof(t_philo));
	if (!*philos)
		return (false);
	memset(*philos, 0, rules->number_of_philosophers * sizeof(t_philo));
	i = 0;
	while (i < rules->number_of_philosophers)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].start_time = start_time;
		(*philos)[i].state = ALIVE;
		(*philos)[i].state_mutex = &mutexes->state_mutexes[i];
		(*philos)[i].sync_mutex = mutexes->sync_mutex;
		(*philos)[i].print_mutex = mutexes->print_mutex;
		set_forks(*philos, mutexes->forks, rules, i);
		(*philos)[i].is_outsider = is_outsider(rules, (*philos)[i].id);
		(*philos)[i].initial_time_to_think_us = calc_initial_think_us(rules, (*philos)[i].id);
		(*philos)[i].time_to_think_us = calc_time_to_think_us(rules, (*philos)[i].id);
		(*philos)[i].rules = rules;
		i++;
	}
	return (true);
}
