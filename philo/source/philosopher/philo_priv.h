/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priv_philo.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:09:47 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 16:38:37 by ldulling         ###   ########.fr       */
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
# include <stdio.h>
# include <unistd.h>

bool	philo_eat(t_philo *me);
bool	philo_sleep(t_philo *me);
bool	philo_think(t_philo *me, unsigned int thinking_time_us);
bool	philo_think_initial(t_philo *me, unsigned int thinking_time_us);
bool	usleep_while_alive(unsigned int us, t_philo *philo);
bool	usleep_while_alive_precise(unsigned int us, t_philo *philo);

#endif
