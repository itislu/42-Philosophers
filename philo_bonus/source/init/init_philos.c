/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:16:53 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/11 10:21:10 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

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
		(*philos)[i].base_ptr = *philos;
		(*philos)[i].id = i + 1;
		(*philos)[i].start_time = start_time;
		(*philos)[i].rules = rules;
		(*philos)[i].state = ALIVE;
		(*philos)[i].semaphores = semaphores;
		(*philos)[i].is_outsider = calc_is_outsider(rules, (*philos)[i].id);
		(*philos)[i].initial_think_time_us = calc_initial_think_time_us(
				rules, (*philos)[i].id);
		(*philos)[i].think_time_us = calc_think_time_us(rules);
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
