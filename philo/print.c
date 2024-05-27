/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:20:29 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/27 01:41:47 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_if_alive(t_philo *me, useconds_t print_delay, const char *msg)
{
	(void)print_delay;
	if (print_delay > 0)
		usleep(print_delay);
	if (!check_alive(me))
		return (false);
	print_msg(me, msg);
	return (true);
}

void	print_msg(t_philo *me, const char *msg)
{
	char	buffer[256];

	snprintf(buffer, 256, msg, me->latest_timestamp, me->id);
	if (me->id % 2 == 1)
	 	printf("%s", buffer);
	else
		printf(SPACING "%s", buffer);
}

// Might have impact on performance
void	print_db(t_philo *me, const char *msg)
{
	if (me->id % 2 == 1)
		dprintf(2, "%llu %d %s\n", get_elapsed_time_ms((struct timeval *)me->start_time), me->id, msg);
	else
		dprintf(2, SPACING "%llu %d %s" STY_RES "\n", get_elapsed_time_ms((struct timeval *)me->start_time), me->id, msg);
}

// Might have impact on performance
void	print_db_death(t_philo *me)
{
	if (me->id % 2 == 1)
		dprintf(2, "  - %d died %llums after last meal\n", me->id, me->latest_timestamp - me->last_meal_timestamp);
	else
		dprintf(2, SPACING "  - %d died %llums after last meal" STY_RES "\n", me->id, me->latest_timestamp - me->last_meal_timestamp);
}
