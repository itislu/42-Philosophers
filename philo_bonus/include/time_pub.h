/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_pub.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:04:05 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/05 10:38:16 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_PUB_H
# define TIME_PUB_H

# include <stddef.h>
# include <sys/time.h>

unsigned long long	get_elapsed_time_ms(const struct timeval *start_time);
unsigned long long	get_elapsed_time_us(const struct timeval *start_time);
unsigned long long	get_remaining_time_us(const struct timeval *target_time);
struct timeval		*increase_target_time(struct timeval *target_time, unsigned long long increase_us);

#endif
