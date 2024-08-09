/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pub.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:28:05 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 17:35:55 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_PUB_H
# define INIT_PUB_H

# include "monitor_pub.h"
# include "philo_pub.h"
# include "rules_pub.h"
# include "semaphores.h"
# include <stdbool.h>
# include <sys/time.h>

typedef enum e_exit_codes
{
	SUCCESS				=	0,
	INPUT_ERROR			=	1,
	SEMAPHORE_FAILURE	=	2,
	MALLOC_FAILURE		=	3,
	PROCESS_FAILURE		=	4,
	THREAD_FAILURE		=	5
}	t_exit;

/* Error Messages */
# define ERR_SEMAPHORE	"Error: Semaphore initialization failed\n"
# define ERR_MALLOC		"Error: Memory allocation failed\n"
# define ERR_PROCESS	"Error: Process creation failed\n"
# define ERR_THREAD		"Error: Thread creation failed\n"

bool	create_philo_processes(t_philo *philos, int count);
void	stop_philo_processes(t_philo *philos, int count);
bool	init_semaphores(t_semaphores *semaphores, int num_of_philos);
void	destroy_semaphores(t_semaphores *semaphores);
bool	init_philos(
			t_philo **philos,
			t_semaphores *semaphores,
			const t_rules *rules,
			struct timeval *start_time);
void	cleanup(t_philo *philos, t_semaphores *semaphores, char *error_msg);
void	init_monitor(
			t_mon *monitor,
			t_philo *philos,
			t_semaphores *semaphores,
			t_rules *rules);

#endif
