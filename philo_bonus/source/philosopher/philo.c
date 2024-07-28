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

void	clean_exit(t_philo *me, int exit_status)
{
	destroy_semaphores(me->semaphores);
	free(me->base_ptr);
	exit(exit_status);
}

void	philosopher(t_philo *me)
{
	sem_wait(me->semaphores->sync.sem);
	sem_post(me->semaphores->sync.sem);
	if (VERBOSE)
		print_verbose(me, "has started routine");
	if (me->initial_think_time_us)
		if (!philo_think_initial(me))
			clean_exit(me, 1);	// No verbose message atm
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
	clean_exit(me, me->state & DEAD);
}
