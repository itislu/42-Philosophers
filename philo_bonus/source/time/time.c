/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:37:28 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/06 04:45:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time_priv.h"

unsigned long long	to_us(const struct timeval *time)
{
	return (time->tv_sec * 1000000ULL + time->tv_usec);
}

unsigned long long	get_elapsed_time_ms(const struct timeval *start_time)
{
	struct timeval	current_time;
	struct timeval	result;

	gettimeofday(&current_time, NULL);
	timersub(&current_time, start_time, &result);
	return (result.tv_sec * 1000ULL + result.tv_usec / 1000);
}

unsigned long long	get_elapsed_time_us(const struct timeval *start_time)
{
	struct timeval	current_time;
	struct timeval	result;

	gettimeofday(&current_time, NULL);
	timersub(&current_time, start_time, &result);
	return (to_us(&result));
}

unsigned long long	get_remaining_time_us(
						const struct timeval *target_time, t_philo *me)
{
	struct timeval	current_time;
	struct timeval	result;

	gettimeofday(&current_time, NULL);
	if (timercmp(&current_time, target_time, >))
	{
		if (VERBOSE)
		{
			timersub(&current_time, target_time, &result);
			print_verbose_us(me,
				STY_BOL STY_BLU "is behind cycle target time by" STY_RES,
				to_us(&result));
		}
		return (0);
	}
	timersub(target_time, &current_time, &result);
	return (to_us(&result));
}

struct timeval	*increase_target_time(
					struct timeval *target_time,
					unsigned long long increase_us)
{
	struct timeval	increase;

	increase.tv_sec = increase_us / 1000000;
	increase.tv_usec = increase_us % 1000000;
	timeradd(target_time, &increase, target_time);
	return (target_time);
}
