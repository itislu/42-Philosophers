/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:01:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 10:58:54 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULATE_H
# define CALCULATE_H

# include "typedefs.h"
# include <stdbool.h>

bool			is_outsider(const t_rules *rules, int id);
unsigned int	calc_initial_think_us(const t_rules *rules, int id);
unsigned int	calc_thinking_time_us(const t_rules *rules, int id);

#endif
