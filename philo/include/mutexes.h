/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:41:54 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 16:58:40 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEXES_H
# define MUTEXES_H

# include <pthread.h>

typedef struct s_mutexes
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*state_mutexes;
	pthread_mutex_t	*sync_mutex;
	pthread_mutex_t	*print_mutex;
}	t_mutexes;

#endif
