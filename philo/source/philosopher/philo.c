/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:54:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 11:04:05 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "priv_philo.h"
#include "typedefs.h"
#include <pthread.h>
#include <stdbool.h>

void	*philosopher(void *arg)
{
	t_philo	*me;

	me = (t_philo *)arg;
	pthread_mutex_lock(me->sync_mutex);
	pthread_mutex_unlock(me->sync_mutex);
	if (me->initial_thinking_time_us)
		if (!philo_think_initial(me, me->initial_thinking_time_us))
			return (NULL);
	while (true)
	{
		if (!philo_eat(me))
			break ;
		if (!philo_sleep(me))
			break ;
		if (!philo_think(me, me->thinking_time_us))
			break ;
	}
	me->release_forks(me);
	print_verbose(me, "has exited routine");
	return (NULL);
}
