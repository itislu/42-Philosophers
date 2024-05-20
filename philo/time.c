/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:37:28 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/20 18:38:38 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_elapsed_time_ms(struct timeval start_time)
{
	struct timeval		current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - start_time.tv_sec) * 1000 +
			(current_time.tv_usec - start_time.tv_usec) / 1000);
}

unsigned long long	get_elapsed_time_us(struct timeval start_time)
{
	struct timeval		current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - start_time.tv_sec) * 1000000 +
			(current_time.tv_usec - start_time.tv_usec));
}
