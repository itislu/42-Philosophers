/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:36:09 by ldulling          #+#    #+#             */
/*   Updated: 2024/07/30 01:37:43 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor_priv.h"

static int	get_philo_id_with_pid(t_philo *philos, pid_t pid);
static void	wait_all_stopped(t_mon *monitor, int num_of_philos);
static void	print_death(t_philo *philos, int dead_philo);

void	broadcast_death(t_mon *monitor)
{
	int		status;
	pid_t	pid;

	sem_post(monitor->semaphores->stop.sem);
	wait_all_stopped(monitor, monitor->rules->num_of_philos);
	pid = waitpid(0, &status, 0);
	print_death(monitor->philos, get_philo_id_with_pid(monitor->philos, pid));
	sem_post(monitor->semaphores->exit_allowed.sem);
}

static int	get_philo_id_with_pid(t_philo *philos, pid_t pid)
{
	int	i;

	i = 0;
	while (i < philos->rules->num_of_philos)
	{
		if (philos[i].pid == pid)
			break ;
		i++;
	}
	return (i);
}

static void	wait_all_stopped(t_mon *monitor, int num_of_philos)
{
	int	i;

	if (VERBOSE)
		print_verbose_monitor(monitor, "waits for all philos to be stopped");
	i = 0;
	while (i < num_of_philos)
	{
		sem_wait(monitor->semaphores->ready_to_exit.sem);
		i++;
	}
}

static void	print_death(t_philo *philos, int dead_philo)
{
	print_msg(&philos[dead_philo], MSG_DEAD);
}
