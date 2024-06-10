/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:01:01 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 06:35:02 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned int	calc_even_us(const t_rules *rules, int id);
static unsigned int	calc_odd_us(const t_rules *rules, int id);

bool	is_outsider(const t_rules *rules, int id)
{
	if (rules->num_of_philos % 2 == 1 && rules->num_of_philos > 1
		&& id == rules->num_of_philos)
		return (true);
	return (false);
}

unsigned int	calc_initial_think_us(const t_rules *rules, int id)
{
	if (rules->num_of_philos < 2)
		return (rules->time_to_die_us + 1000);
	else if (rules->num_of_philos % 2 == 0)
		return (calc_even_us(rules, id));
	else
		return (calc_odd_us(rules, id));
}

unsigned int	calc_thinking_time_us(const t_rules *rules, int id)
{
	(void)id;
	if (rules->time_to_eat_ms > rules->time_to_sleep_ms + MARGIN_MS / 2)
		return ((rules->time_to_eat_ms - rules->time_to_sleep_ms
				- MARGIN_MS / 2) * 1000U);
	else
		return (0);
}

static unsigned int	calc_even_us(const t_rules *rules, int id)
{
	(void)rules;
	if (id % 2 == 0)
		return (MARGIN_MS / 2 * 1000);
	else
		return (0);
}

static unsigned int	calc_odd_us(const t_rules *rules, int id)
{
	if (is_outsider(rules, id))
		return ((rules->time_to_eat_ms * 2 - MARGIN_MS / 2) * 1000U);
	else if (id % 2 == 0)
		return (MARGIN_MS / 2 * 1000);
	else
		return (0);
}
