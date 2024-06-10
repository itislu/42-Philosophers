/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_priv.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:01:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 16:34:28 by ldulling         ###   ########.fr       */
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
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

bool			is_outsider(const t_rules *rules, int id);
unsigned int	calc_initial_think_us(const t_rules *rules, int id);
unsigned int	calc_thinking_time_us(const t_rules *rules, int id);

#endif
