/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   margin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:51:14 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 18:34:42 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_priv.h"

unsigned long long	get_initial_think_margin_us(const t_rules *rules)
{
	return (rules->time_to_eat_ms / 2 * 1000ULL);
}

unsigned long long	get_think_margin_us(void)
{
	return (DEATH_MARGIN_MS / 2 * 1000ULL);
}
