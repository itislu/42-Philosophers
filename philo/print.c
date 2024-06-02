/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:20:29 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/03 00:10:09 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_nothing_to_do(t_rules *rules)
{
	if (rules->number_of_philosophers == 0)
		printf("No philosophers at the table.\n");
	if (rules->number_of_times_each_philosopher_must_eat == 0)
		printf("No meals to serve.\n");
}

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
	char	*spacing;

	if (me->is_outsider)
		spacing = SPACING SPACING;
	else if (me->id % 2 == 0)
		spacing = SPACING;
	else
		spacing = "";
	pthread_mutex_lock(me->print_mutex);
	printf(msg, spacing, me->latest_timestamp, me->id);
	pthread_mutex_unlock(me->print_mutex);
}

void	print_verbose(t_philo *me, const char *msg)
{
	char	*spacing;

	if (!VERBOSE)
		return ;
	if (me->is_outsider)
		spacing = SPACING SPACING;
	else if (me->id % 2 == 0)
		spacing = SPACING;
	else
		spacing = "";
	pthread_mutex_lock(me->print_mutex);
	dprintf(2, "%s%llu %d %s\n", spacing, get_elapsed_time_ms((struct timeval *)me->start_time), me->id, msg);
	pthread_mutex_unlock(me->print_mutex);
}

void	print_verbose_death(t_philo *me)
{
	char	*spacing;

	if (!VERBOSE)
		return ;
	if (me->is_outsider)
		spacing = SPACING SPACING;
	else if (me->id % 2 == 0)
		spacing = SPACING;
	else
		spacing = "";
	pthread_mutex_lock(me->print_mutex);
	dprintf(2, "%s  - %d died %llums after last meal\n", spacing, me->id, me->latest_timestamp - me->last_meal_timestamp);
	pthread_mutex_unlock(me->print_mutex);
}
