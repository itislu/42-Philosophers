/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:16:53 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/27 01:20:38 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_mutexes(void *ptr, int count, size_t obj_size, size_t offset)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(ptr + i * obj_size + offset, NULL) != 0)
		{
			destroy_mutexes(ptr, i, obj_size, offset);
			return (false);
		}
		i++;
	}
	return (true);
}

void	destroy_mutexes(void *ptr, int count, size_t obj_size, size_t offset)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(ptr + i * obj_size + offset);
		i++;
	}
}

static useconds_t	calc_even_us(const t_rules *rules, int i)
{
	(void)rules;
	if (i % 2 == 0)
		return (0);
	else
		return (10 * 1000);
}

static useconds_t	calc_odd_us(const t_rules *rules, int i)
{
	(void)rules;
	if (i % 2 == 0)
		return (0);
	else
		return (10 * 1000);
}

useconds_t	calc_initial_think_us(const t_rules *rules, int i)
{
	if (rules->number_of_philosophers < 2)
		return (rules->time_to_die_us + USLEEP_LONG_US);
	else if (rules->number_of_philosophers % 2 == 0)
		return (calc_even_us(rules, i));
	else
		return (calc_odd_us(rules, i));
}

useconds_t	calc_time_to_think_us(const t_rules *rules, int i)
{
	(void)i;
	if (rules->time_to_eat_ms > rules->time_to_sleep_ms)
		return ((rules->time_to_eat_ms - rules->time_to_sleep_ms) * 1000U);
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

bool	init_philos(t_philo *philos, pthread_mutex_t *forks, const t_rules *rules, pthread_mutex_t *sync_mutex, struct timeval *start_time)
{
	int	i;

	if (pthread_mutex_init(sync_mutex, NULL) != 0)
		return (false);
	if (!init_mutexes(philos, rules->number_of_philosophers, sizeof(t_philo), offsetof(t_philo, state_mutex)))
		return (pthread_mutex_destroy(sync_mutex), false);
	i = 0;
	while (i < rules->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].start_time = start_time;
		philos[i].state = ALIVE;
		philos[i].sync_mutex = sync_mutex;
		set_forks(philos, forks, rules, i);
		philos[i].initial_time_to_think_us = calc_initial_think_us(rules, i);
		philos[i].time_to_think_us = calc_time_to_think_us(rules, i);
		philos[i].rules = rules;
		philos[i].meals_remaining = rules->number_of_times_each_philosopher_must_eat;
		i++;
	}
	return (true);
}
