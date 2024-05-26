/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:15:26 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/26 16:34:02 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Use the following macros for time comparison:
//    void timeradd(struct timeval *a, struct timeval *b, struct timeval *res);
//    void timersub(struct timeval *a, struct timeval *b, struct timeval *res);
//    void timerclear(struct timeval *tvp);
//    int timerisset(struct timeval *tvp);
//    int timercmp(struct timeval *a, struct timeval *b, CMP);

void	print_actual_slept_time(struct timeval *start, struct timeval *end, useconds_t us, t_philo *philo)
{
	struct timeval		result;
	unsigned long long	actual_slept_time_us;

	timersub(end, start, &result);
	actual_slept_time_us = result.tv_sec * 1000000ULL + result.tv_usec;

	if (actual_slept_time_us - us >= 50)
	{
		if (philo->id % 2 == 1)
		{
			dprintf(2, STY_BOL STY_RED SPACING "%llu %d Target sleep time: %u us" STY_RES "\n", get_elapsed_time_ms(philo->start_time), philo->id, us);
			dprintf(2, STY_BOL STY_RED SPACING "%llu %d Actual sleep time: %llu us" STY_RES "\n", get_elapsed_time_ms(philo->start_time), philo->id, actual_slept_time_us);
		}
		else
		{
			dprintf(2, STY_BOL STY_RED "%llu %d Target sleep time: %u us" STY_RES "\n", get_elapsed_time_ms(philo->start_time), philo->id, us);
			dprintf(2, STY_BOL STY_RED "%llu %d Actual sleep time: %llu us" STY_RES "\n", get_elapsed_time_ms(philo->start_time), philo->id, actual_slept_time_us);
		}
	}
}

// Function that usleeps and prints out the actual time slept
void	usleep_and_print(useconds_t us, t_philo *philo)
{
	struct timeval		start;
	struct timeval		end;

	gettimeofday(&start, NULL);
	// if (us > 100)
		usleep(us);
	gettimeofday(&end, NULL);

	// print_actual_slept_time(&start, &end, us, philo);
	(void)philo;
}

void	busy_wait(useconds_t us)
{
	struct timeval	start_time;

	dprintf(2, "Busy wait for %u us\n", us);
	gettimeofday(&start_time, NULL);
	while (get_elapsed_time_us(&start_time) < us)
		;
}

bool	usleep_while_alive(useconds_t us, t_philo *philo)
{
	struct timeval	start_time;
	useconds_t		slept_time_us;

	gettimeofday(&start_time, NULL);
	slept_time_us = 0;
	while (slept_time_us + USLEEP_SHORT_THRESHOLD_US < us)
	{
		if (!check_alive(philo))
			return (false);
		usleep_and_print(USLEEP_LONG_US, philo);
		slept_time_us = get_elapsed_time_us(&start_time);
	}
	while (slept_time_us + BUSY_WAIT_THRESHOLD_US < us)
	{
		// if (!check_alive(philo))
		// 	return (false);
		usleep_and_print(USLEEP_SHORT_US, philo);
		slept_time_us = get_elapsed_time_us(&start_time);
	}
	if (slept_time_us < us)
	{
		print_db(philo, "busy waits");
		busy_wait(us - slept_time_us);
	}

	struct timeval	end_time;
	gettimeofday(&end_time, NULL);
	print_actual_slept_time(&start_time, &end_time, us, philo);

	return (true);
}

// bool	usleep_batch(useconds_t us, useconds_t sleep_time_us, t_philo *philo)
// {
// 	struct timeval	start_time;

// 	gettimeofday(&start_time, NULL);
// 	while (get_elapsed_time_us(start_time) < us)
// 	{
// 		if (!check_alive(philo))
// 			return (false);
// 		usleep_and_print(sleep_time_us, philo);
// 	}
// 	return (true);
// }

// bool	usleep_while_alive_new(useconds_t us, t_philo *philo)
// {
// 	struct timeval	start_time;
// 	useconds_t		slept_time_us;

// 	gettimeofday(&start_time, NULL);
// 	if (USLEEP_SHORT_THRESHOLD_US < us)
// 		if (!usleep_batch(us - USLEEP_SHORT_THRESHOLD_US, USLEEP_LONG_US, philo))
// 			return (false);
// 	slept_time_us = get_elapsed_time_us(start_time);
// 	if (slept_time_us + BUSY_WAIT_THRESHOLD_US < us)
// 		if (!usleep_batch(us - slept_time_us - BUSY_WAIT_THRESHOLD_US, USLEEP_SHORT_US, philo))
// 			return (false);
// 	slept_time_us = get_elapsed_time_us(start_time);
// 	if (slept_time_us < us)
// 	{
// 		print_db(philo, "busy waits");
// 		busy_wait(us - slept_time_us);
// 	}

// 	struct timeval	end_time;
// 	gettimeofday(&end_time, NULL);
// 	print_actual_slept_time(&start_time, &end_time, us, philo);

// 	return (true);
// }

bool	usleep_while_alive_old(useconds_t us, t_philo *philo)
{
	struct timeval	start_time;
	useconds_t		sleep_time_us;
	useconds_t		slept_time_us;

	gettimeofday(&start_time, NULL);
	if (us > 1000)
		sleep_time_us = 1000;
	else
		sleep_time_us = us;
	slept_time_us = 0;
	while (slept_time_us + 1100 < us)
	{
		if (!check_alive(philo))
			return (false);
		usleep_and_print(sleep_time_us, philo);
		slept_time_us = get_elapsed_time_us(&start_time);
	}
	while (slept_time_us + 110 < us)
	{
		usleep_and_print(sleep_time_us, philo);
		slept_time_us = get_elapsed_time_us(&start_time);
	}

	if (!check_alive(philo))
		return (false);
	//? The question is whether usleeping multiple times for small amount is more accurate than usleeping once for a larger amount
	// while (slept_time_us < us)
	// {
	// 	sleep_time_us = us - slept_time_us;
	// 	// sleep_time_us /= 2;
	// 	// if (!check_alive(philo))
	// 	// 	return (false);
	// 	// usleep(sleep_time_us);
	// 	usleep(sleep_time_us / 10);
	// 	slept_time_us = get_elapsed_time_us(&start_time);
	// }
	slept_time_us = get_elapsed_time_us(&start_time);
	if (slept_time_us < us)
		usleep_and_print(us - slept_time_us, philo);

	struct timeval	end_time;
	gettimeofday(&end_time, NULL);
	print_actual_slept_time(&start_time, &end_time, us, philo);

	return (true);
}
