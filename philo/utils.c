/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:15:26 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/20 21:29:55 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

//TODO Still need to dynamically calculate a fitting usleep time
/*
- There should be a maximum.
-
*/
bool	usleep_while_alive(useconds_t us, t_philo *philo)
{
	struct timeval	start_time;
	useconds_t		sleep_time_us;
	// unsigned long long	slept_time_us;

	sleep_time_us = us / 2 % 1000000;
	if (sleep_time_us < 100)
		sleep_time_us = 0;
	// slept_time_us = 0;
	gettimeofday(&start_time, NULL);
	while (get_elapsed_time_us(start_time) < us)
	{
		// if (slept_time_us % 1000000 < sleep_time_us)
		// {
			if (!check_alive(philo))
				return (false);
		// }
		if (sleep_time_us)
		{
			usleep(sleep_time_us);
			// slept_time_us += sleep_time_us;
			sleep_time_us = us / 2 % 1000000;
			if (sleep_time_us < 100)
				sleep_time_us = 0;
		}
	}
	return (true);
}
