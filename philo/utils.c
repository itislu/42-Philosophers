/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:15:26 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/02 02:54:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#if VERBOSE

void	print_actual_elapsed_time(struct timeval *start, struct timeval *end, useconds_t target_time_us, t_philo *philo)
{
	struct timeval		result;
	unsigned long long	actual_time_us;
	char				verbose_msg1[100];
	char				verbose_msg2[100];

	timersub(end, start, &result);
	actual_time_us = result.tv_sec * 1000000ULL + result.tv_usec;
	if (actual_time_us - target_time_us >= VERBOSE_USLEEP_DELAY_THRESHOLD_US)
	{
		snprintf(verbose_msg1, 100,
			STY_BOL STY_RED "Target sleep time: %uus" STY_RES, target_time_us);
		snprintf(verbose_msg2, 100,
			STY_BOL STY_RED "Actual sleep time: %lluus" STY_RES, actual_time_us);
		print_verbose(philo, verbose_msg1);
		print_verbose(philo, verbose_msg2);
	}
}

#endif

useconds_t	usleep_return(useconds_t us, struct timeval *start_time)
{
	usleep(us);
	return (get_elapsed_time_us(start_time));
}

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
