/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_priv.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:09:47 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/07 02:02:48 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PRIV_H
# define PHILO_PRIV_H

# include "macros.h"
# include "print_pub.h"
# include "philo_pub.h"
# include "time_pub.h"
# include "typedefs.h"
# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>

bool	philo_eat(t_philo *me);
bool	philo_sleep(t_philo *me);
bool	philo_think_initial(t_philo *me);
bool	philo_think(t_philo *me);
bool	usleep_while_alive(unsigned long long us, t_philo *me);
bool	usleep_while_alive_precise(unsigned long long us, t_philo *me);
bool	usleep_while_alive_precise_target(
			const struct timeval *target_time, t_philo *me, const char *msg);

#endif
