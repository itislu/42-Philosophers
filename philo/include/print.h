/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:15:47 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 10:44:07 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "typedefs.h"
# include <stdbool.h>

bool	print_if_alive(t_philo *me, const char *msg);
void	print_msg(t_philo *me, const char *msg);
void	print_verbose(t_philo *me, const char *msg);
void	print_verbose_death(t_philo *me);
void	print_actual_elapsed_time(
			struct timeval *start,
			struct timeval *end,
			unsigned int target_time_us,
			t_philo *philo);


#endif