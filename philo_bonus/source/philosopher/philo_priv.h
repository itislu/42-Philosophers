/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_priv.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:09:47 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 18:46:56 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PRIV_H
# define PHILO_PRIV_H

# include "init_pub.h"
# include "print_pub.h"
# include "philo_pub.h"
# include "semaphores.h"
# include "time_pub.h"
# include "utils_pub.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* Usleep Timings */
# define USLEEP_LONG_US				1000
# define USLEEP_SHORT_THRESHOLD_US	2000
# define USLEEP_SHORT_US			100
# define BUSY_WAIT_THRESHOLD_US		100

bool	philo_eat(t_philo *me);
bool	philo_sleep(t_philo *me);
bool	philo_think_initial(t_philo *me);
bool	philo_think(t_philo *me);
bool	take_forks(t_philo *me);
void	release_forks(t_philo *me);
bool	usleep_while_alive(unsigned long long us, t_philo *me);
bool	usleep_while_alive_precise(unsigned long long us, t_philo *me);
bool	usleep_while_alive_precise_target(
			const struct timeval *target_time, t_philo *me, const char *msg);
void	set_is_stopped(t_philo *me);
bool	get_is_stopped(t_philo *me);

#endif
