/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:15:26 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/22 01:07:07 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

bool	usleep_while_alive(useconds_t us, t_philo *philo)
{
	struct timeval		start_time;
	useconds_t			sleep_time_us;
	unsigned long long	slept_time_us;

	gettimeofday(&start_time, NULL);
	if (us > 1000)
		sleep_time_us = 1000;
	else
		sleep_time_us = us;
	slept_time_us = 0;
	while (slept_time_us + 1000 >= us)
	{
		if (!check_alive(philo))
			return (false);
		usleep(sleep_time_us);
		slept_time_us = get_elapsed_time_us(start_time);
	}
	while (slept_time_us < us)
	{
		sleep_time_us /= 2;
		if (!check_alive(philo))
			return (false);
		usleep(sleep_time_us / 10);
		slept_time_us = get_elapsed_time_us(start_time);
	}
	return (true);
}
