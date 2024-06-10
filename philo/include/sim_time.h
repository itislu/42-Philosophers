/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_time.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:04:05 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 10:43:03 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIM_TIME_H
# define SIM_TIME_H

# include <stddef.h>
# include <sys/time.h>

unsigned long long	get_elapsed_time_ms(struct timeval *start_time);
unsigned long long	get_elapsed_time_us(struct timeval *start_time);

#endif
