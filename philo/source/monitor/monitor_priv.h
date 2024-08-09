/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_priv.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:37:19 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 18:39:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_PRIV_H
# define MONITOR_PRIV_H

# include "monitor_pub.h"
# include "philo_pub.h"
# include "print_pub.h"
# include "rules_pub.h"
# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>

# define MONITOR_INTERVAL_US	433

void	print_death(t_philo *philos, int num_of_philos, int dead_philo);

#endif