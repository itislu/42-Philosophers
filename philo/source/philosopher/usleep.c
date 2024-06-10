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

static unsigned int	usleep_return(unsigned int us, struct timeval *start_time)
					__attribute__((always_inline));
static void			busy_wait(
						unsigned int us,
						unsigned int duration_us,
						struct timeval *start_time,
						t_philo *philo)
					__attribute__((always_inline));

bool	usleep_while_alive(unsigned int us, t_philo *philo)
{
	struct timeval	start_time;
	unsigned int	slept_time_us;

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

bool	usleep_while_alive_precise(unsigned int us, t_philo *philo)
{
	struct timeval	start_time;
	struct timeval	end_time;
	unsigned int	slept_time_us;

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

static __attribute__((always_inline))
unsigned int	usleep_return(unsigned int us, struct timeval *start_time)
{
	usleep(us);
	return (get_elapsed_time_us(start_time));
}

static __attribute__((always_inline))
void	busy_wait(
			unsigned int us,
			unsigned int duration_us,
			struct timeval *start_time,
			t_philo *philo)
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
