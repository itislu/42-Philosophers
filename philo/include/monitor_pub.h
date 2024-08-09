/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_pub.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:19:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 17:10:38 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_PUB_H
# define MONITOR_PUB_H

# include "rules_pub.h"
# include "philo_pub.h"

void	monitor(t_philo *philos, const t_rules *rules);
void	broadcast(t_philo *philos, t_state state, int num_of_philos);

#endif
