/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:51:10 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 13:48:17 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"
#include <signal.h>
#include <sys/wait.h>

bool	create_philo_processes(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		philos[i].pid = fork();
		if (philos[i].pid == -1)
		{
			// broadcast_death(philos, i);
			// pthread_mutex_unlock(philos[i].sync_mutex);
			kill_philo_processes(philos, i);
			return (false);
		}
		else if (philos[i].pid == 0)
			philosopher(&philos[i]);
		i++;
	}
	return (true);
}

void	kill_philo_processes(t_philo *philos, int count)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < count)
	{
		if (VERBOSE)
			print_verbose(&philos[i], "will be joined");
		kill(philos[i].pid, SIGTERM);
		if (VERBOSE)
			print_verbose(&philos[i], "has been joined");
		i++;
	}
	i = 0;
	while (i < count)
	{
		waitpid(philos[i].pid, &wstatus, 0);
		i++;
	}
}
