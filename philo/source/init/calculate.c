/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:01:01 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 05:08:16 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static useconds_t	calc_even_us(const t_rules *rules, int id);
static useconds_t	calc_odd_us(const t_rules *rules, int id);

bool	is_outsider(const t_rules *rules, int id)
{
	if (rules->number_of_philosophers % 2 == 1
		&& rules->number_of_philosophers > 1
		&& id == rules->number_of_philosophers)
		return (true);
	return (false);
}

useconds_t	calc_initial_think_us(const t_rules *rules, int id)
{
	if (rules->number_of_philosophers < 2)
		return (rules->time_to_die_us + 1000);
	else if (rules->number_of_philosophers % 2 == 0)
		return (calc_even_us(rules, id));
	else
		return (calc_odd_us(rules, id));
}

useconds_t	calc_thinking_time_us(const t_rules *rules, int id)
{
	(void)id;
	if (rules->time_to_eat_ms > rules->time_to_sleep_ms + MARGIN_MS / 2)
		return ((rules->time_to_eat_ms - rules->time_to_sleep_ms
				- MARGIN_MS / 2) * 1000U);
	else
		return (0);
}

static useconds_t	calc_even_us(const t_rules *rules, int id)
{
	(void)rules;
	if (id % 2 == 0)
		return (MARGIN_MS / 2 * 1000);
	else
		return (0);
}

static useconds_t	calc_odd_us(const t_rules *rules, int id)
{
	if (is_outsider(rules, id))
		return ((rules->time_to_eat_ms * 2 - MARGIN_MS / 2) * 1000U);
	else if (id % 2 == 0)
		return (MARGIN_MS / 2 * 1000);
	else
		return (0);
}
