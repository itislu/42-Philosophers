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

bool	create_philo_processes(t_philo *philos, int count);
void	kill_philo_processes(t_philo *philos, int count);
bool	init_semaphores(t_semaphores *semaphores, int count);
void	destroy_semaphores(t_semaphores *semaphores, int count);
bool	init_philos(
			t_philo **philos,
			t_semaphores *semaphores,
			const t_rules *rules,
			struct timeval *start_time);

#endif
