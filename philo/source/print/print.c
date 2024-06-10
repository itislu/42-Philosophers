/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:20:29 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 04:40:26 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_if_alive(t_philo *me, const char *msg)
{
	if (!check_alive(me))
		return (false);
	print_msg(me, msg);
	return (true);
}

void	print_msg(t_philo *me, const char *msg)
{
	char	*spacing;

	if (me->is_outsider)
		spacing = COLUMN3;
	else if (me->id % 2 == 0)
		spacing = COLUMN2;
	else
		spacing = COLUMN1;
	pthread_mutex_lock(me->print_mutex);
	me->latest_timestamp = get_elapsed_time_ms((struct timeval *)me->start_time);
	printf(msg, spacing, me->latest_timestamp, me->id);
	pthread_mutex_unlock(me->print_mutex);
}
