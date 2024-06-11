/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:26:22 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/11 10:38:14 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_priv.h"

void	print_verbose(t_philo *me, const char *msg)
{
	char	*spacing;

	if (!VERBOSE)
		return ;
	if (me->is_outsider)
		spacing = COLUMN3;
	else if (me->id % 2 == 0)
		spacing = COLUMN2;
	else
		spacing = COLUMN1;
	pthread_mutex_lock(me->print_mutex);
	dprintf(STDERR_FILENO, "%s%llu %d %s\n", spacing,
		get_elapsed_time_ms((struct timeval *)me->start_time), me->id, msg);
	pthread_mutex_unlock(me->print_mutex);
}

void	print_verbose_death(t_philo *me)
{
	char	*spacing;

	if (!VERBOSE)
		return ;
	if (me->is_outsider)
		spacing = COLUMN3;
	else if (me->id % 2 == 0)
		spacing = COLUMN2;
	else
		spacing = COLUMN1;
	pthread_mutex_lock(me->print_mutex);
	dprintf(STDERR_FILENO, "%s%llu %d died %llums after last meal\n",
		spacing, get_elapsed_time_ms((struct timeval *)me->start_time), me->id,
		me->latest_timestamp_ms - me->last_meal_timestamp_ms);
	pthread_mutex_unlock(me->print_mutex);
}

void	print_verbose_monitor(t_philo *philo, const char *msg)
{
	if (!VERBOSE)
		return ;
	pthread_mutex_lock(philo->print_mutex);
	dprintf(STDERR_FILENO, STY_BOL "%s%llu %c %s\n" STY_RES, COLUMN1,
		get_elapsed_time_ms((struct timeval *)philo->start_time), 'm', msg);
	pthread_mutex_unlock(philo->print_mutex);
}

#if VERBOSE

void	print_actual_elapsed_time(
			struct timeval *start,
			struct timeval *end,
			unsigned long long target_time_us,
			t_philo *me)
{
	struct timeval		result;
	unsigned long long	actual_time_us;
	char				verbose_msg1[100];
	char				verbose_msg2[100];

	timersub(end, start, &result);
	actual_time_us = result.tv_sec * 1000000ULL + result.tv_usec;
	if (actual_time_us - target_time_us >= VERBOSE_DELAY_PRINT_THRESHOLD_US)
	{
		snprintf(verbose_msg1, 100, STY_BOL STY_RED "Target sleep time: %lluus"
			STY_RES, target_time_us);
		snprintf(verbose_msg2, 100, STY_BOL STY_RED "Actual sleep time: %lluus"
			STY_RES, actual_time_us);
		print_verbose(me, verbose_msg1);
		print_verbose(me, verbose_msg2);
	}
}

#endif
