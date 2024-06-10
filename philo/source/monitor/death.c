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

static void	wait_all_dead(t_philo *philos, int num_of_philos);

void	broadcast_death(t_philo *philos, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_lock(philos[i].state_mutex);
		philos[i].state |= DEAD;
		pthread_mutex_unlock(philos[i].state_mutex);
		i++;
	}
}

void	print_death(t_philo *philos, int num_of_philos, int dead_philo)
{
	wait_all_dead(philos, num_of_philos);
	print_msg(&philos[dead_philo], MSG_DEAD);
}

static void	wait_all_dead(t_philo *philos, int num_of_philos)
{
	int		i;
	t_state	state;

	while (true)
	{
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
}
