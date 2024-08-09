/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_pub.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:04:05 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 16:59:00 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_PUB_H
# define TIME_PUB_H

# include "philo_pub.h"
# include <sys/time.h>

/* Timing Configuration */
# define MONITOR_INTERVAL_US		433
# define USLEEP_LONG_US				1000
# define USLEEP_SHORT_THRESHOLD_US	2000
# define USLEEP_SHORT_US			100
# define BUSY_WAIT_THRESHOLD_US		100
# define MARGIN_MS					10

unsigned long long	to_us(const struct timeval *time);
unsigned long long	get_elapsed_time_ms(const struct timeval *start_time);
unsigned long long	get_elapsed_time_us(const struct timeval *start_time);
unsigned long long	get_remaining_time_us(
						const struct timeval *target_time, t_philo *me);
struct timeval		*increase_target_time(
						struct timeval *target_time,
						unsigned long long increase_us);

#endif
