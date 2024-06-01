/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:27:30 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/01 12:48:18 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_take_fork(t_philo *me, pthread_mutex_t *fork)
{
	// if (!check_alive(me))
	// 	return (false);
	//* The too late death time was bc it was stuck in this mutex
	if (pthread_mutex_lock(fork) != 0)
		return (false);
	if (!print_if_alive(me, DFLT_PRINT_DELAY_US, MSG_FORK))
	{
		pthread_mutex_unlock(fork);
		return (false);
	}
	return (true);
}

bool	take_forks_left_first(t_philo *me)
{
	print_debug(me, "is trying to take forks");
	if (!philo_take_fork(me, me->left_fork))
		return (false);
	me->locked_left_fork = true;
	print_debug(me, "has taken left fork");
	if (!philo_take_fork(me, me->right_fork))
		return (false);
	me->locked_right_fork = true;
	print_debug(me, "has taken right fork");
	return (true);
}

bool	take_forks_right_first(t_philo *me)
{
	print_debug(me, "is trying to take forks");
	if (!philo_take_fork(me, me->right_fork))
		return (false);
	me->locked_right_fork = true;
	print_debug(me, "has taken right fork");
	if (!philo_take_fork(me, me->left_fork))
		return (false);
	me->locked_left_fork = true;
	print_debug(me, "has taken left fork");
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
