/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:37:28 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/05 11:49:10 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time_pub.h"

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
	return (result.tv_sec * 1000000ULL + result.tv_usec);
}

unsigned long long	get_remaining_time_us(const struct timeval *target_time)
{
	struct timeval	current_time;
	struct timeval	result;

	gettimeofday(&current_time, NULL);
	if (!timercmp(&current_time, target_time, <))
		return (0);
	timersub(target_time, &current_time, &result);
	return (result.tv_sec * 1000000ULL + result.tv_usec);
}

#include <stdio.h>
struct timeval	*increase_target_time(struct timeval *target_time, unsigned long long increase_us)
{
	struct timeval	increase;

	increase.tv_sec = increase_us / 1000000;
	increase.tv_usec = increase_us % 1000000;
	timeradd(target_time, &increase, target_time);
	// printf("increased by %llu\n", increase_us);
	return (target_time);
}
