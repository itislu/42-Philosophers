/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pub.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:28:05 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 17:41:13 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_PUB_H
# define INIT_PUB_H

# include "mutexes.h"
# include "philo_pub.h"
# include "rules_pub.h"
# include <stdbool.h>
# include <sys/time.h>

enum e_exit_codes
{
	SUCCESS			=	0,
	INPUT_ERROR		=	1,
	MUTEX_FAILURE	=	2,
	MALLOC_FAILURE	=	3,
	THREAD_FAILURE	=	4
};

/* Error Messages */
# define ERR_MUTEX		"Error: Mutex initialization failed\n"
# define ERR_MALLOC		"Error: Memory allocation failed\n"
# define ERR_THREAD		"Error: Thread creation failed\n"

bool	create_philo_threads(t_philo *philos, int count);
void	join_philo_threads(t_philo *philos, int count);
bool	init_mutexes(t_mutexes *mutexes, int count);
void	destroy_mutexes(t_mutexes *mutexes, int count);
bool	init_philos(
			t_philo **philos,
			t_mutexes *mutexes,
			const t_rules *rules,
			struct timeval *start_time);

#endif
