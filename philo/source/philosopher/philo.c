/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:54:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/05 14:15:06 by ldulling         ###   ########.fr       */
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
	me->target_time = *me->start_time;
	if (me->initial_think_time_us)
		if (!philo_think_initial(me))
			return (verbose_exit(me));
	if (VERBOSE)
		print_verbose_us(me, STY_BOL STY_YEL "target_time: " STY_RES, me->target_time.tv_sec * 1000 + me->target_time.tv_usec / 1000 - (me->start_time->tv_sec * 1000 + me->start_time->tv_usec / 1000));
	while (true)
	{
		if (!philo_eat(me))
			break ;
		if (VERBOSE)
			print_verbose_us(me, STY_BOL STY_MAG "target_time: " STY_RES, me->target_time.tv_sec * 1000 + me->target_time.tv_usec / 1000 - (me->start_time->tv_sec * 1000 + me->start_time->tv_usec / 1000));
		if (!philo_sleep(me))
			break ;
		if (VERBOSE)
			print_verbose_us(me, STY_BOL STY_BLU "target_time: " STY_RES, me->target_time.tv_sec * 1000 + me->target_time.tv_usec / 1000 - (me->start_time->tv_sec * 1000 + me->start_time->tv_usec / 1000));
		if (!philo_think(me))
			break ;
		if (VERBOSE)
			print_verbose_us(me, STY_BOL STY_YEL "target_time: " STY_RES, me->target_time.tv_sec * 1000 + me->target_time.tv_usec / 1000 - (me->start_time->tv_sec * 1000 + me->start_time->tv_usec / 1000));
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
