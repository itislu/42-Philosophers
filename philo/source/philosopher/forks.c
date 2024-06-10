/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:27:30 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 11:42:32 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "macros.h"
#include "typedefs.h"
#include <pthread.h>
#include <stdbool.h>

static __attribute__((always_inline))
bool	philo_take_fork(t_philo *me, pthread_mutex_t *fork)
{
	if (pthread_mutex_lock(fork) != 0)
		return (false);
	if (!print_if_alive(me, MSG_FORK))
	{
		pthread_mutex_unlock(fork);
		return (false);
	}
	return (true);
}

bool	take_forks_left_first(t_philo *me)
{
	print_verbose(me, "is trying to take forks");
	if (!philo_take_fork(me, me->left_fork))
		return (false);
	me->locked_left_fork = true;
	print_verbose(me, "has taken left fork");
	if (!philo_take_fork(me, me->right_fork))
		return (false);
	me->locked_right_fork = true;
	print_verbose(me, "has taken right fork");
	return (true);
}

bool	take_forks_right_first(t_philo *me)
{
	print_verbose(me, "is trying to take forks");
	if (!philo_take_fork(me, me->right_fork))
		return (false);
	me->locked_right_fork = true;
	print_verbose(me, "has taken right fork");
	if (!philo_take_fork(me, me->left_fork))
		return (false);
	me->locked_left_fork = true;
	print_verbose(me, "has taken left fork");
	return (true);
}

void	release_forks_left_first(t_philo *me)
{
	if (me->locked_left_fork)
	{
		pthread_mutex_unlock(me->left_fork);
		me->locked_left_fork = false;
	}
	if (me->locked_right_fork)
	{
		pthread_mutex_unlock(me->right_fork);
		me->locked_right_fork = false;
	}
}

void	release_forks_right_first(t_philo *me)
{
	if (me->locked_right_fork)
	{
		pthread_mutex_unlock(me->right_fork);
		me->locked_right_fork = false;
	}
	if (me->locked_left_fork)
	{
		pthread_mutex_unlock(me->left_fork);
		me->locked_left_fork = false;
	}
}
