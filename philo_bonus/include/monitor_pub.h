/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_pub.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:19:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 17:42:16 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_PUB_H
# define MONITOR_PUB_H

# include "rules_pub.h"
# include "philo_pub.h"
# include "semaphores.h"
# include <stdbool.h>

typedef struct s_monitor
{
	t_philo			*philos;
	t_semaphores	*semaphores;
	const t_rules	*rules;
	bool			is_released;
}	t_mon;

bool	monitor(t_mon *monitor);

#endif
