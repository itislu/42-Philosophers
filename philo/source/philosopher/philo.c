/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:54:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/06 03:46:46 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

static void	*verbose_exit(t_philo *me);

void	*philosopher(void *arg)
{
	t_philo	*me;

	me = (t_philo *)arg;
	pthread_mutex_lock(me->sync_mutex);
	pthread_mutex_unlock(me->sync_mutex);
	if (VERBOSE)
		print_verbose(me, "has started routine");
	me->cycle_target_time = *me->start_time;
	if (me->initial_think_time_us)
		if (!philo_think_initial(me))
			return (verbose_exit(me));
	while (true)
	{
		if (!philo_eat(me))
			break ;
		if (!philo_sleep(me))
			break ;
		if (!philo_think(me))
			break ;
	}
	me->release_forks(me);
	return (verbose_exit(me));
}

static void	*verbose_exit(t_philo *me)
{
	if (VERBOSE)
		print_verbose(me, "has exited routine");
	return (NULL);
}
