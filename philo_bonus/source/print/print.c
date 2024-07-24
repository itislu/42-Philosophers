/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:20:29 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/11 10:37:55 by ldulling         ###   ########.fr       */
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

	if (me->is_outsider)
		spacing = COLUMN3;
	else if (me->id % 2 == 0)
		spacing = COLUMN2;
	else
		spacing = COLUMN1;
	me->latest_timestamp_ms = get_elapsed_time_ms(me->start_time);
	printf(msg, spacing, me->latest_timestamp_ms, me->id);
}
