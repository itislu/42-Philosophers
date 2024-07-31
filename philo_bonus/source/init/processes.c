/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:51:10 by ldulling          #+#    #+#             */
/*   Updated: 2024/07/30 01:23:43 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

bool	create_philo_processes(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		philos[i].pid = fork();
		if (philos[i].pid == -1)
		{
			stop_philo_processes(philos, i);
			return (false);
		}
		else if (philos[i].pid == 0)
			philosopher(&philos[i]);
		i++;
	}
	return (true);
}

void	stop_philo_processes(t_philo *philos, int count)
{
	int	i;
	int	status;

	sem_post(philos->semaphores->stop.sem);
	sem_post(philos->semaphores->exit_allowed.sem);
	i = 0;
	while (i < count)
	{
		waitpid(philos[i].pid, &status, 0);
		i++;
	}
}
