/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:20:29 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/04 17:44:30 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_priv.h"

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

	if (COLUMN2 && ft_iseven(me->id))
		spacing = COLUMN2;
	else
		spacing = COLUMN1;
	pthread_mutex_lock(me->print_mutex);
	me->latest_timestamp_ms = get_elapsed_time_ms(me->start_time);
	printf(msg, spacing, me->latest_timestamp_ms, me->id);
	pthread_mutex_unlock(me->print_mutex);
}
