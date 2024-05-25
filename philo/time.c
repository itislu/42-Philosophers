/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:37:28 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/25 15:53:18 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_elapsed_time_ms(struct timeval *start_time)
{
	struct timeval		current_time;
	struct timeval		result;

	gettimeofday(&current_time, NULL);
	timersub(&current_time, start_time, &result);
	return ((unsigned long long)result.tv_sec * 1000 + result.tv_usec / 1000);
}

unsigned long long	get_elapsed_time_us(struct timeval *start_time)
{
	struct timeval		current_time;
	struct timeval		result;

	gettimeofday(&current_time, NULL);
	timersub(&current_time, start_time, &result);
	return ((unsigned long long)result.tv_sec * 1000000 + result.tv_usec);
}
