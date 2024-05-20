/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barrier.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:22:22 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/20 21:34:36 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <errno.h>
#include <unistd.h>

#define BARRIER_BUSY_WAIT_USEC	1000

typedef struct s_barrier
{
	pthread_mutex_t			mutex;
	unsigned int			needed;
	volatile unsigned int	waiting;
}	t_barrier;

int	barrier_init(t_barrier *barrier, unsigned int needed);
int	barrier_destroy(t_barrier *barrier);
int	barrier_wait(t_barrier *barrier);
