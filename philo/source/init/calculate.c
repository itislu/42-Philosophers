/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:01:01 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/04 02:01:34 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

bool	calc_is_outsider(const t_rules *rules, int id)
{
	if (rules->num_of_philos % 2 == 1 && rules->num_of_philos > 1
		&& id == rules->num_of_philos)
		return (true);
	return (false);
}

unsigned long long	calc_think_time_us(const t_rules *rules)
{
	// if ((unsigned long long)rules->time_to_eat_ms
	// 	> (unsigned long long)rules->time_to_sleep_ms + MARGIN_MS / 2)
	// 	return ((rules->time_to_eat_ms - rules->time_to_sleep_ms
	// 			- MARGIN_MS / 2) * 1000ULL);
	// else
	// 	return (0);
	return (2ULL * rules->time_to_eat_ms / (rules->num_of_philos - rules->num_of_philos % 2) * 1000ULL);
}

unsigned long long	calc_initial_think_time_us(const t_rules *rules, int id, unsigned long long think_time_us)
{
	if (rules->num_of_philos < 2)
		return ((rules->time_to_die_ms + 1ULL) * 1000ULL);
	else
	{
		int	block_amount;

		block_amount = id / 2;
		if (id % 2 == 0)
			block_amount += rules->num_of_philos / 2;
		return (think_time_us * block_amount);
	}
}
