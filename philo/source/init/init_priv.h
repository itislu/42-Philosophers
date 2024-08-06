/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_priv.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:01:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/06 01:25:59 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_PRIV_H
# define INIT_PRIV_H

# include "init_pub.h"
# include "macros.h"
# include "monitor_pub.h"
# include "print_pub.h"
# include "philo_pub.h"
# include "typedefs.h"
# include "utils_pub.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

unsigned long long	calc_initial_think_time_us(const t_rules *rules, int id);
unsigned long long	calc_think_time_us(const t_rules *rules);
unsigned long long	calc_initial_cycle_time_us(
						const t_rules *rules, t_philo *philo);
unsigned long long	calc_cycle_time_us(const t_rules *rules, t_philo *philo);

#endif
