/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:01:01 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/06 01:28:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

static unsigned long long	calc_think_block_us(const t_rules *rules);

unsigned long long	calc_initial_think_time_us(const t_rules *rules, int id)
{
	int	block_amount;

	if (rules->num_of_philos < 2)
		return (rules->time_to_die_ms * 1000ULL);
	else if (ft_iseven(rules->num_of_philos))
	{
		if (ft_iseven(id))
			return (rules->time_to_eat_ms / 2 * 1000ULL);
		else
			return (0);
	}
	else
	{
		block_amount = id / 2;
		if (ft_iseven(id))
			block_amount += rules->num_of_philos / 2;
		return (calc_think_block_us(rules) * block_amount);
	}
}

unsigned long long	calc_think_time_us(const t_rules *rules)
{
	long long	think_time_us;

	think_time_us = (rules->time_to_eat_ms - rules->time_to_sleep_ms
			- MARGIN_MS / 2) * 1000LL;
	if (!ft_iseven(rules->num_of_philos))
		think_time_us += (long long)calc_think_block_us(rules);
	return (ft_max(think_time_us, 0));
}

unsigned long long	calc_initial_cycle_time_us(
						const t_rules *rules, t_philo *philo)
{
	unsigned long long	initial_cycle_time_us;

	initial_cycle_time_us = ((unsigned long long)rules->time_to_eat_ms
			+ rules->time_to_sleep_ms) * 1000 + philo->think_time_us;
	if (ft_iseven(rules->num_of_philos) && ft_iseven(philo->id))
		initial_cycle_time_us += rules->time_to_eat_ms / 2 * 1000ULL;
	return (initial_cycle_time_us);
}

unsigned long long	calc_cycle_time_us(const t_rules *rules, t_philo *philo)
{
	unsigned long long	cycle_time_us;

	cycle_time_us = ((unsigned long long)rules->time_to_eat_ms
			+ rules->time_to_sleep_ms) * 1000 + philo->think_time_us;
	if (philo->think_time_us)
		cycle_time_us += MARGIN_MS / 2 * 1000;
	return (cycle_time_us);
}

static unsigned long long	calc_think_block_us(const t_rules *rules)
{
	if (rules->num_of_philos < 2)
		return (rules->time_to_die_ms * 1000ULL);
	else
		return (2ULL * rules->time_to_eat_ms * 1000ULL
			/ ft_round_down_even(rules->num_of_philos));
}
