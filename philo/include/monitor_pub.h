/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_pub.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:19:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 16:28:39 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_PUB_H
# define MONITOR_PUB_H

# include "typedefs.h"

void	monitor(t_philo *philos, const t_rules *rules);
void	broadcast_death(t_philo *philos, int num_of_philos);

#endif
