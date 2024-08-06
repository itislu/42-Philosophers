/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:16:53 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/07 01:15:45 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

static void	init_philo(
				t_philo *philo,
				t_semaphores *semaphores,
				const t_rules *rules,
				struct timeval *start_time);

bool	init_philos(
			t_philo **philos,
			t_semaphores *semaphores,
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
		init_philo(*philos, semaphores, rules, start_time);
		i++;
	}
	return (true);
}

void	cleanup(t_philo *philos, t_semaphores *semaphores, char *error_msg)
{
	if (error_msg)
		ft_putstr_fd(error_msg, STDERR_FILENO);
	stop_philo_processes(philos, philos->rules->num_of_philos);
	free(philos);
	destroy_semaphores(semaphores);
}

static void	init_philo(
				t_philo *philos,
				t_semaphores *semaphores,
				const t_rules *rules,
				struct timeval *start_time)
{
	static int	i = 0;
	t_philo		*philo;

	philo = &philos[i];
	philo->base_ptr = philos;
	philo->id = i + 1;
	philo->start_time = start_time;
	philo->rules = rules;
	philo->semaphores = semaphores;
	philo->initial_think_time_us = calc_initial_think_time_us(rules, philo->id);
	philo->think_time_us = calc_think_time_us(rules);
	philo->initial_cycle_time_us = calc_initial_cycle_time_us(rules, philo);
	philo->cycle_time_us = calc_cycle_time_us(rules, philo);
	i++;
}
