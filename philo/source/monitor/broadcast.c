/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:36:09 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/04 14:14:15 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor_priv.h"

static void	wait_all_dead(t_philo *philos, int num_of_philos);

void	broadcast(t_philo *philos, t_state state, int num_of_philos)
{
	int	i;

	if (VERBOSE)
		print_verbose_monitor(philos, "broadcasts");
	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_lock(philos[i].state_mutex);
		philos[i].state |= state;
		pthread_mutex_unlock(philos[i].state_mutex);
		i++;
	}
	if (VERBOSE)
		print_verbose_monitor(philos, "finished broadcasting");
}

void	print_death(t_philo *philos, int num_of_philos, int dead_philo)
{
	wait_all_dead(philos, num_of_philos);
	print_msg(&philos[dead_philo], MSG_DEAD);
}

static void	wait_all_dead(t_philo *philos, int num_of_philos)
{
	t_state	state;
	int		i;

	if (VERBOSE)
		print_verbose_monitor(philos, "waits for all death confirms");
	while (true)
	{
		usleep(MONITOR_INTERVAL_US);
		i = 0;
		state = ~0;
		while (i < num_of_philos)
		{
			pthread_mutex_lock(philos[i].state_mutex);
			state &= philos[i].state;
			pthread_mutex_unlock(philos[i].state_mutex);
			i++;
		}
		if ((state & (DEAD | CONFIRMED)) == (DEAD | CONFIRMED))
			break ;
	}
	if (VERBOSE)
		print_verbose_monitor(philos, "got all death confirms");
}
