/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:19:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 10:44:07 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# include "typedefs.h"

void	monitor(t_philo *philos, t_rules rules);
void	broadcast_death(t_philo *philos, int num_of_philos);

#endif