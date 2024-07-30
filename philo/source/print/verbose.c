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
	if (COLUMN3 && me->is_outsider)
		spacing = COLUMN3;
	else if (COLUMN2 && me->id % 2 == 0)
		spacing = COLUMN2;
	else
		spacing = COLUMN1;
	pthread_mutex_lock(me->print_mutex);
	printf("%s%llu %d %s\n", spacing,
		get_elapsed_time_ms(me->start_time), me->id, msg);
	pthread_mutex_unlock(me->print_mutex);
}

void	print_verbose_us(t_philo *me, const char *msg, unsigned long long us)
{
	char	*spacing;

	if (!VERBOSE)
		return ;
	if (COLUMN3 && me->is_outsider)
		spacing = COLUMN3;
	else if (COLUMN2 && me->id % 2 == 0)
		spacing = COLUMN2;
	else
		spacing = COLUMN1;
	pthread_mutex_lock(me->print_mutex);
	printf("%s%llu %d %s %lluus\n", spacing,
		get_elapsed_time_ms(me->start_time), me->id, msg, us);
	pthread_mutex_unlock(me->print_mutex);
}

void	print_verbose_death(t_philo *me)
{
	char	*spacing;

	if (!VERBOSE)
		return ;
	if (COLUMN3 && me->is_outsider)
		spacing = COLUMN3;
	else if (COLUMN2 && me->id % 2 == 0)
		spacing = COLUMN2;
	else
		spacing = COLUMN1;
	pthread_mutex_lock(me->print_mutex);
	printf("%s%llu %d died %llums after last meal\n", spacing,
		get_elapsed_time_ms(me->start_time), me->id,
		me->latest_timestamp_ms - me->last_meal_timestamp_ms);
	pthread_mutex_unlock(me->print_mutex);
}

void	print_verbose_monitor(t_philo *philo, const char *msg)
{
	if (!VERBOSE)
		return ;
	pthread_mutex_lock(philo->print_mutex);
	printf(STY_BOL "%s%llu %c %s" STY_RES "\n", COLUMN1,
		get_elapsed_time_ms(philo->start_time), 'm', msg);
	pthread_mutex_unlock(philo->print_mutex);
}

void	print_actual_elapsed_time(
			struct timeval *start,
			unsigned long long target_time_us,
			t_philo *me)
{
	struct timeval		end;
	struct timeval		result;
	unsigned long long	actual_time_us;

	if (!VERBOSE)
		return ;
	gettimeofday(&end, NULL);
	timersub(&end, start, &result);
	actual_time_us = result.tv_sec * 1000000ULL + result.tv_usec;
	if (actual_time_us - target_time_us >= VERBOSE_DELAY_PRINT_THRESHOLD_US)
	{
		print_verbose_us(
			me, STY_BOL STY_RED "Target sleep time:" STY_RES, target_time_us);
		print_verbose_us(
			me, STY_BOL STY_RED "Actual sleep time:" STY_RES, actual_time_us);
	}
}
