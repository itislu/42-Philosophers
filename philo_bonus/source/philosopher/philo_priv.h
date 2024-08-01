/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_priv.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:09:47 by ldulling          #+#    #+#             */
/*   Updated: 2024/07/30 01:39:56 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PRIV_H
# define PHILO_PRIV_H

# include "init_pub.h"
# include "macros.h"
# include "print_pub.h"
# include "philo_pub.h"
# include "time_pub.h"
# include "typedefs.h"
# include "utils_pub.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

bool	philo_eat(t_philo *me);
bool	philo_sleep(t_philo *me);
bool	philo_think_initial(t_philo *me);
bool	philo_think(t_philo *me);
bool	take_forks(t_philo *me);
void	release_forks(t_philo *me);
bool	usleep_while_alive(unsigned long long us, t_philo *me);
bool	usleep_while_alive_precise(unsigned long long us, t_philo *me);
void	set_is_stopped(t_philo *me);
bool	get_is_stopped(t_philo *me);

#endif
