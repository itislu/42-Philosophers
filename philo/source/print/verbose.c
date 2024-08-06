/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:26:22 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/06 03:38:16 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if VERBOSE

# include "print_priv.h"

#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include "ft_printf.h"
#include "libft.h"

// Function to get the current time in nanoseconds
long long get_current_time_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

void print_verbose(t_philo *me, const char *msg) {
    char *spacing;

    if (COLUMN2 && ft_iseven(me->id))
        spacing = COLUMN2;
    else
        spacing = COLUMN1;

    pthread_mutex_lock(me->print_mutex);

    // Measure time for printf
    long long start_time_printf = get_current_time_ns();
    printf("%s%llu %d %s\n", spacing,
        get_elapsed_time_ms(me->start_time), me->id, msg);
    long long end_time_printf = get_current_time_ns();
    long long elapsed_time_printf = end_time_printf - start_time_printf;

    // Measure time for ft_snprintf
	char buffer[100];
    long long start_time_ft_snprintf = get_current_time_ns();
    ft_snprintf(buffer, 100, "%s%d %d %s\n", spacing,
        get_elapsed_time_ms(me->start_time), me->id, msg);
	ft_putstr_fd(buffer, 1);
    long long end_time_ft_snprintf = get_current_time_ns();
    long long elapsed_time_ft_snprintf = end_time_ft_snprintf - start_time_ft_snprintf;

    // Measure time for ft_printf
    long long start_time_ft_printf = get_current_time_ns();
    ft_printf("%s%d %d %s\n", spacing,
        get_elapsed_time_ms(me->start_time), me->id, msg);
    long long end_time_ft_printf = get_current_time_ns();
    long long elapsed_time_ft_printf = end_time_ft_printf - start_time_ft_printf;

    // Measure time for ft_put
    long long start_time_ft_put = get_current_time_ns();
	ft_putstr_fd(spacing, 1);
	ft_putnbr_fd(get_elapsed_time_ms(me->start_time), 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(me->id, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd((char *)msg, 1);
	ft_putchar_fd('\n', 1);
    long long end_time_ft_put = get_current_time_ns();
    long long elapsed_time_ft_put = end_time_ft_put - start_time_ft_put;

    pthread_mutex_unlock(me->print_mutex);

    // Print the elapsed times
    printf("printf took %lld ns\n", elapsed_time_printf);
    printf("ft_snprintf took %lld ns\n", elapsed_time_ft_snprintf);
    printf("ft_printf took %lld ns\n", elapsed_time_ft_printf);
    printf("ft_put took %lld ns\n", elapsed_time_ft_put);
}

void	print_verbose_us(t_philo *me, const char *msg, unsigned long long us)
{
	char	*spacing;

	if (COLUMN2 && ft_iseven(me->id))
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

	if (COLUMN2 && ft_iseven(me->id))
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

	gettimeofday(&end, NULL);
	timersub(&end, start, &result);
	actual_time_us = to_us(&result);
	if (actual_time_us - target_time_us >= VERBOSE_DELAY_PRINT_THRESHOLD_US)
	{
		print_verbose_us(
			me, STY_BOL STY_RED "Target sleep time:" STY_RES, target_time_us);
		print_verbose_us(
			me, STY_BOL STY_RED "Actual sleep time:" STY_RES, actual_time_us);
	}
}

#endif
