/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:01:01 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/11 10:20:47 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

static unsigned int	calc_initial_even_us(int id);
static unsigned int	calc_initial_odd_us(const t_rules *rules, int id);

bool	calc_is_outsider(const t_rules *rules, int id)
{
	if (rules->num_of_philos % 2 == 1 && rules->num_of_philos > 1
		&& id == rules->num_of_philos)
		return (true);
	return (false);
}

unsigned int	calc_thinking_time_us(const t_rules *rules)
{
	if (rules->time_to_eat_ms > rules->time_to_sleep_ms + MARGIN_MS / 2)
		return ((rules->time_to_eat_ms - rules->time_to_sleep_ms
				- MARGIN_MS / 2) * 1000U);
	else
		return (0);
}

unsigned int	calc_initial_thinking_time_us(const t_rules *rules, int id)
{
	if (rules->num_of_philos < 2)
		return (rules->time_to_die_us + 1000);
	else if (rules->num_of_philos % 2 == 0)
		return (calc_initial_even_us(id));
	else
		return (calc_initial_odd_us(rules, id));
}

static unsigned int	calc_initial_even_us(int id)
{
	if (id % 2 == 0)
		return (MARGIN_MS / 2 * 1000);
	else
		return (0);
}

static unsigned int	calc_initial_odd_us(const t_rules *rules, int id)
{
	if (calc_is_outsider(rules, id))
		return ((rules->time_to_eat_ms * 2 - MARGIN_MS / 2) * 1000U);
	else if (id % 2 == 0)
		return (MARGIN_MS / 2 * 1000);
	else
		return (0);
}
