/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:27:30 by ldulling          #+#    #+#             */
/*   Updated: 2024/07/30 01:06:19 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

static inline __attribute__((always_inline))
bool	philo_take_fork(t_philo *me, sem_t *forks)
{
	sem_wait(forks);
	if (!print_if_alive(me, MSG_FORK))
	{
		sem_post(forks);
		return (false);
	}
	me->forks_taken++;
	return (true);
}

bool	take_forks(t_philo *me)
{
	if (VERBOSE)
		print_verbose(me, "is trying to take forks");
	while (me->forks_taken < 2)
		if (!philo_take_fork(me, me->semaphores->forks.sem))
			return (false);
	return (true);
}

void	release_forks(t_philo *me)
{
	if (me->forks_taken <= 0)
		return ;
	while (me->forks_taken > 0)
	{
		sem_post(me->semaphores->forks.sem);
		me->forks_taken--;
	}
	if (VERBOSE)
		print_verbose(me, "has released forks");
}
