/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:26:22 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/02 09:45:06 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if VERBOSE

# include "print_priv.h"

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
	sem_wait(me->semaphores->print_mutex.sem);
	printf("%s%llu %d %s\n", spacing,
		get_elapsed_time_ms(me->start_time), me->id, msg);
	sem_post(me->semaphores->print_mutex.sem);
}

void	print_verbose_us(t_philo *me, const char *msg, unsigned long long us)
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
	sem_wait(me->semaphores->print_mutex.sem);
	printf("%s%llu %d %s %lluus\n", spacing,
		get_elapsed_time_ms(me->start_time), me->id, msg, us);
	sem_post(me->semaphores->print_mutex.sem);
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
	sem_wait(me->semaphores->print_mutex.sem);
	printf("%s%llu %d died %llums after last meal\n", spacing,
		get_elapsed_time_ms(me->start_time), me->id,
		me->latest_timestamp_ms - me->last_meal_timestamp_ms);
	sem_post(me->semaphores->print_mutex.sem);
}

void	print_verbose_monitor(t_mon *monitor, const char *msg)
{
	if (!VERBOSE)
		return ;
	sem_wait(monitor->semaphores->print_mutex.sem);
	printf(STY_BOL "%s%llu %c %s" STY_RES "\n", COLUMN1,
		get_elapsed_time_ms(monitor->philos->start_time), 'm', msg);
	sem_post(monitor->semaphores->print_mutex.sem);
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

#endif
