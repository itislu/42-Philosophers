/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:55:06 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 13:52:48 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor_priv.h"
#include <sys/wait.h>

int	get_philo_id_with_pid(t_philo *philos, int num_of_philos, pid_t pid)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		if (philos[i].pid == pid)
			break ;
		i++;
	}
	return (i);
}

void	*monitor_is_full(void *arg)
{
	t_philo *philos = (t_philo *)arg;
	t_semaphores *semaphores = philos->semaphores;
	const t_rules *rules = philos->rules;
	int	i;

	i = 0;
	while (i < rules->num_of_philos)
	{
		sem_wait(semaphores->is_full.sem);
		i++;
	}
	if (VERBOSE)
		print_verbose_monitor(philos, "All philosophers got full");
	sem_post(semaphores->ready_to_exit.sem);
	return (NULL);
}

void	*monitor_is_dead(void *arg)
{
	t_philo *philos = (t_philo *)arg;
	t_semaphores *semaphores = philos->semaphores;
	const t_rules *rules = philos->rules;
	int		wstatus;
	pid_t	pid;

	sem_wait(semaphores->is_dead.sem);
	pid = waitpid(0, &wstatus, 0);
	broadcast_death(philos, rules->num_of_philos);
	print_death(philos, rules->num_of_philos,
					get_philo_id_with_pid(philos, rules->num_of_philos, pid));
	sem_post(semaphores->ready_to_exit.sem);
	return (NULL);
}

void	monitor(t_philo *philos, t_semaphores *semaphores, const t_rules *rules)
{
	pthread_t	monitors[2];

	(void)rules;
	// Create two threads and detach them. On one, monitor the is_full semaphore; on the other, monitor the is_dead semaphore.
	// Only one of them will get enough sem_posts to continue and set the read_to_exit semaphore.
	// When exiting a process, all its threads gets terminated automatically.
	pthread_create(&monitors[0], NULL, &monitor_is_full, philos);
	pthread_create(&monitors[1], NULL, &monitor_is_dead, philos);
	pthread_detach(monitors[0]);
	pthread_detach(monitors[1]);

	sem_wait(semaphores->ready_to_exit.sem);
}

// void	monitor(t_philo *philos, t_rules rules)
// {
// 	int		wstatus;
// 	pid_t	pid;
// 	int		i;
//
// 	i = 0;
// 	while (i < rules.num_of_philos)
// 	{
// 		pid = waitpid(0, &wstatus, 0);
// 		if (pid == -1)
// 			//error
// 		else if (WIFEXITED(wstatus))
// 		{
// 			if (WEXITSTATUS(wstatus) == 0)
// 				// got full
// 			else
// 			{
// 				broadcast_death(philos, rules.num_of_philos);
// 				print_death(philos, rules.num_of_philos,
// 					get_philo_id_with_pid(philos, rules.num_of_philos, pid));
// 				return ;
// 			}
// 		}
// 		else
// 			// terminated by signal
// 		i++;
// 	}
// 	// sem_wait(philos->kill_semaphore);
// 	if (VERBOSE)
// 		print_verbose_monitor(philos, "All philosophers got full");
// }
