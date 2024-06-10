/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:15:26 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 02:41:45 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static __attribute__((always_inline))
useconds_t	usleep_return(useconds_t us, struct timeval *start_time)
{
	usleep(us);
	return (get_elapsed_time_us(start_time));
}

static __attribute__((always_inline))
void	busy_wait(useconds_t us, useconds_t duration_us, struct timeval *start_time, t_philo *philo)
{
	char	verbose_msg[100];

	if (VERBOSE)
	{
		snprintf(verbose_msg, 100, "busy waits for %uus", duration_us);
		print_verbose(philo, verbose_msg);
	}
	while (get_elapsed_time_us(start_time) < us)
		;
}

bool	usleep_while_alive(useconds_t us, t_philo *philo)
{
	struct timeval	start_time;
	useconds_t		slept_time_us;

	gettimeofday(&start_time, NULL);
	slept_time_us = 0;
	while (slept_time_us < us)
	{
		if (!check_alive(philo))
			return (false);
		slept_time_us = usleep_return(USLEEP_LONG_US, &start_time);
	}
	return (true);
}

bool	usleep_while_alive_precise(useconds_t us, t_philo *philo)
{
	struct timeval	start_time;
	struct timeval	end_time;
	useconds_t		slept_time_us;

	gettimeofday(&start_time, NULL);
	slept_time_us = 0;
	while (slept_time_us + USLEEP_SHORT_THRESHOLD_US < us)
	{
		if (!check_alive(philo))
			return (false);
		slept_time_us = usleep_return(USLEEP_LONG_US, &start_time);
	}
	while (slept_time_us + BUSY_WAIT_THRESHOLD_US < us)
		slept_time_us = usleep_return(USLEEP_SHORT_US, &start_time);
	if (slept_time_us < us && check_alive(philo))
		busy_wait(us, us - slept_time_us, &start_time, philo);
	if (VERBOSE)
	{
		gettimeofday(&end_time, NULL);
		print_actual_elapsed_time(&start_time, &end_time, us, philo);
	}
	return (true);
}
