/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_pub.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:04:05 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 18:36:51 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_PUB_H
# define TIME_PUB_H

# include "philo_pub.h"
# include <sys/time.h>

unsigned long long	to_us(const struct timeval *time);
unsigned long long	get_elapsed_time_ms(const struct timeval *start_time);
unsigned long long	get_elapsed_time_us(const struct timeval *start_time);
unsigned long long	get_remaining_time_us(
						const struct timeval *target_time, t_philo *me);
struct timeval		*increase_target_time(
						struct timeval *target_time,
						unsigned long long increase_us);

#endif
