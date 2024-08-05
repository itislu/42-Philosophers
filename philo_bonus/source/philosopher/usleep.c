/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:15:26 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/05 22:30:49 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_priv.h"

static inline unsigned long long	usleep_return(
										unsigned int us,
										struct timeval *start_time)
									__attribute__((always_inline));
static inline void				busy_wait(
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

bool	usleep_while_alive_precise_target(
			const struct timeval *target_time, t_philo *me)
{
	unsigned long long remaining_time_us = get_remaining_time_us(target_time);
	if (VERBOSE)
		print_verbose_us(me, STY_BOL STY_BLU "thinking for " STY_RES, remaining_time_us / 1000);
	return (usleep_while_alive_precise(get_remaining_time_us(target_time), me));
}

// bool	usleep_while_alive_timeval_precise(unsigned long long us, struct timeval *start_time, t_philo *me)
// {
// 	unsigned long long	slept_time_us;

// 	slept_time_us = 0;
// 	while (slept_time_us + USLEEP_SHORT_THRESHOLD_US < us)
// 	{
// 		if (!check_alive(me))
// 			return (false);
// 		slept_time_us = usleep_return(USLEEP_LONG_US, (struct timeval *)me->start_time);
// 	}
// 	while (slept_time_us + BUSY_WAIT_THRESHOLD_US < us)
// 		slept_time_us = usleep_return(USLEEP_SHORT_US, (struct timeval *)me->start_time);
// 	if (slept_time_us < us && check_alive(me))
// 		busy_wait(us, us - slept_time_us, (struct timeval *)me->start_time, me);
// 	if (VERBOSE)
// 		print_actual_elapsed_time((struct timeval *)me->start_time, us, me);
// 	return (true);
// }

static inline __attribute__((always_inline))
unsigned long long	usleep_return(
						unsigned int us,
						struct timeval *start_time)
{
	usleep(us);
	return (get_elapsed_time_us(start_time));
}

static inline __attribute__((always_inline))
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
