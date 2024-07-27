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

void	broadcast_death(t_philo *philos, int num_of_philos)
{
	int	i;

	if (VERBOSE)
		print_verbose_monitor(philos, "broadcasts death");
	i = 0;
	while (i < num_of_philos)
	{
		kill(philos[i].pid, SIGTERM);
		i++;
	}
	if (VERBOSE)
		print_verbose_monitor(philos, "finished broadcasting");
}

#include "time_pub.h"
#include <stdio.h>

unsigned long long	debug_get_elapsed_time_ms(const struct timeval *start_time)
{
	struct timeval	current_time;
	struct timeval	result;

	gettimeofday(&current_time, NULL);
	dprintf(2, "haha2.1\n");
	timersub(&current_time, start_time, &result);
	dprintf(2, "haha2.2\n");
	return (result.tv_sec * 1000ULL + result.tv_usec / 1000);
}

void	debug_print_msg(t_philo *me, const char *msg)
{
	char	*spacing;

	dprintf(2, "haha1\n");
	if (me->is_outsider)
		spacing = COLUMN3;
	else if (me->id % 2 == 0)
		spacing = COLUMN2;
	else
		spacing = COLUMN1;
	dprintf(2, "haha2\n");
	me->latest_timestamp_ms = debug_get_elapsed_time_ms(me->start_time);
	dprintf(2, "haha3\n");
	printf(msg, spacing, me->latest_timestamp_ms, me->id);
}

void	print_death(t_philo *philos, int num_of_philos, int dead_philo)
{
	wait_all_dead(philos, num_of_philos);
	dprintf(2, "waited for all deaths\n");

	debug_print_msg(&philos[dead_philo], MSG_DEAD);
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
