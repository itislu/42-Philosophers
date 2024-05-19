/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barrier.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:42:38 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/19 16:28:17 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "barrier.h"

int	barrier_init(t_barrier *barrier, unsigned int needed)
{
	if (needed == 0)
		return (EINVAL);
	barrier->needed = needed;
	barrier->waiting = 0;
	return (pthread_mutex_init(&barrier->mutex, NULL));
}

int	barrier_destroy(t_barrier *barrier)
{
	barrier->needed = 0;
	barrier->waiting = 0;
	return (pthread_mutex_destroy(&barrier->mutex));
}

int	barrier_wait(t_barrier *barrier)
{
	int				ret;
	unsigned int	needed;

	ret = pthread_mutex_lock(&barrier->mutex);
	if (ret != 0)
		return (ret);
	barrier->waiting++;
	needed = barrier->needed;
    ret = pthread_mutex_unlock(&barrier->mutex);
	if (ret != 0)
		return (ret);
	while (barrier->waiting < needed)
		usleep(BARRIER_BUSY_WAIT_USEC);
	return (0);
}
