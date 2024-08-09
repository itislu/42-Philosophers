/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_priv.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:01:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 18:45:06 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_PRIV_H
# define INIT_PRIV_H

# include "init_pub.h"
# include "philo_pub.h"
# include "rules_pub.h"
# include "semaphores.h"
# include "utils_pub.h"
# include <fcntl.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define DEATH_MARGIN_MS	10

unsigned long long	calc_initial_think_time_us(const t_rules *rules, int id);
unsigned long long	calc_think_time_us(const t_rules *rules);
unsigned long long	calc_initial_cycle_time_us(
						const t_rules *rules, t_philo *philo);
unsigned long long	calc_cycle_time_us(const t_rules *rules, t_philo *philo);
unsigned long long	get_initial_think_margin_us(const t_rules *rules);
unsigned long long	get_think_margin_us(void);

#endif
