/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:54:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 16:38:57 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"
#include <stdlib.h>
#include "init_pub.h"

void	clean_exit(t_philo *me, pthread_t monitor, int exit_status)
{
	sem_post(me->semaphores->stop.sem);
	pthread_join(monitor, NULL);
	destroy_semaphores(me->semaphores);
	free(me->base_ptr);
	exit(exit_status);
}

void	*monitor_stop(void *arg)
{
	t_philo			*me;
	t_semaphores	*semaphores;

	me = (t_philo *)arg;
	semaphores = me->semaphores;
	sem_wait(semaphores->stop.sem);
	sem_post(semaphores->stop.sem);
	me->state |= DEAD;
	return (NULL);
}

void	philosopher(t_philo *me)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, &monitor_stop, me);
	sem_wait(me->semaphores->sync.sem);
	sem_post(me->semaphores->sync.sem);
	if (VERBOSE)
		print_verbose(me, "has started routine");
	if (me->initial_think_time_us)
		if (!philo_think_initial(me))
			clean_exit(me, monitor, 1);	// No verbose message atm
	while (true)
	{
		if (!philo_eat(me))
			break ;
		if (!philo_sleep(me))
			break ;
		if (!philo_think(me))
			break ;
	}
	release_forks(me);
	if (VERBOSE)
		print_verbose(me, "has exited routine");
	clean_exit(me, monitor, me->state & DEAD);
}
