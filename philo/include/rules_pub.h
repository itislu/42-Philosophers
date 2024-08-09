/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_pub.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:25:52 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 16:58:29 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RULES_PUB_H
# define RULES_PUB_H

# include <stdbool.h>

typedef struct s_rules
{
	int	num_of_philos;
	int	time_to_die_ms;
	int	time_to_eat_ms;
	int	time_to_sleep_ms;
	int	num_each_philo_must_eat;
}	t_rules;

bool	parse_rules(t_rules *rules, int argc, char *argv[]);
void	print_nothing_to_do(t_rules *rules);

#endif
