/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:27:30 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 17:08:58 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

static __attribute__((always_inline))
bool	philo_take_fork(t_philo *me, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
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
	bool	was_locked;

	if (me->locked_left_fork)
	{
		pthread_mutex_unlock(me->left_fork);
		me->locked_left_fork = false;
		was_locked = true;
	}
	else
		was_locked = false;
	if (me->locked_right_fork)
	{
		pthread_mutex_unlock(me->right_fork);
		me->locked_right_fork = false;
		was_locked = true;
	}
	if (was_locked)
		print_verbose(me, "has released forks");
}

void	release_forks_right_first(t_philo *me)
{
	bool	was_locked;

	if (me->locked_right_fork)
	{
		pthread_mutex_unlock(me->right_fork);
		me->locked_right_fork = false;
		was_locked = true;
	}
	else
		was_locked = false;
	if (me->locked_left_fork)
	{
		pthread_mutex_unlock(me->left_fork);
		me->locked_left_fork = false;
		was_locked = true;
	}
	if (was_locked)
		print_verbose(me, "has released forks");
}
