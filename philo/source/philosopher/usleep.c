/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:15:26 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 16:38:57 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

static unsigned long long	usleep_return(
								unsigned int us, struct timeval *start_time)
							__attribute__((always_inline));
static void					busy_wait(
								unsigned long long us,
								unsigned long long duration_us,
								struct timeval *start_time,
								t_philo *me)
							__attribute__((always_inline));

bool	usleep_while_alive(unsigned long long us, t_philo *me)
{
	struct timeval		start_time;
	unsigned long long	slept_time_us;

	gettimeofday(&start_time, NULL);
	slept_time_us = 0;
	while (slept_time_us < us)
	{
		if (!check_alive(me))
			return (false);
		slept_time_us = usleep_return(USLEEP_LONG_US, &start_time);
	}
	return (true);
}

bool	usleep_while_alive_precise(unsigned long long us, t_philo *me)
{
	struct timeval		start_time;
	unsigned long long	slept_time_us;

	gettimeofday(&start_time, NULL);
	slept_time_us = 0;
	while (slept_time_us + USLEEP_SHORT_THRESHOLD_US < us)
	{
		if (!check_alive(me))
			return (false);
		slept_time_us = usleep_return(USLEEP_LONG_US, &start_time);
	}
	while (slept_time_us + BUSY_WAIT_THRESHOLD_US < us)
		slept_time_us = usleep_return(USLEEP_SHORT_US, &start_time);
	if (slept_time_us < us && check_alive(me))
		busy_wait(us, us - slept_time_us, &start_time, me);
	if (VERBOSE)
		print_actual_elapsed_time(&start_time, us, me);
	return (true);
}

static __attribute__((always_inline))
unsigned long long	usleep_return(
						unsigned int us, struct timeval *start_time)
{
	usleep(us);
	return (get_elapsed_time_us(start_time));
}

static __attribute__((always_inline))
void	busy_wait(
			unsigned long long us,
			unsigned long long duration_us,
			struct timeval *start_time,
			t_philo *me)
{
	if (VERBOSE)
		print_verbose_us(me, "busy waits for", duration_us);
	while (get_elapsed_time_us(start_time) < us)
		;
}
