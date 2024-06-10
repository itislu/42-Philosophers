/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pub.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:28:05 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 16:33:13 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_PUB_H
# define INIT_PUB_H

# include "typedefs.h"
# include <stdbool.h>

bool	create_philo_threads(t_philo *philos, const t_rules *rules);
void	join_philo_threads(t_philo *philos, int count);
bool	init_mutexes(t_mutexes *mutexes, t_rules *rules);
void	destroy_mutexes(t_mutexes *mutexes, t_rules *rules);
bool	init_philos(
			t_philo **philos,
			t_mutexes *mutexes,
			const t_rules *rules,
			struct timeval *start_time);

#endif
