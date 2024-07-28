/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:36:09 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 13:52:41 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor_priv.h"
#include <signal.h>
#include <sys/wait.h>

static void	wait_all_dead(t_philo *philos, int num_of_philos);

void	print_death(t_philo *philos, int num_of_philos, int dead_philo)
{
	wait_all_dead(philos, num_of_philos);
	print_msg(&philos[dead_philo], MSG_DEAD);
}

static void	wait_all_dead(t_philo *philos, int num_of_philos)
{
	int	i;
	int	wstatus;

	if (VERBOSE)
		print_verbose_monitor(philos, "waits for all death confirms");
	i = 0;
	while (i < num_of_philos)
	{
		waitpid(philos[i].pid, &wstatus, 0);
		i++;
	}
}
