/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:07:48 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 13:50:52 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_priv.h"

static bool	set_rule(int *rule, char *target, char *arg);
static bool	is_number(char *arg);
static bool	is_negative(char *arg);

bool	parse_rules(t_rules *rules, int argc, char *argv[])
{
	bool	ret;

	if (argc != 5 && argc != 6)
		return (print_wrong_arg_num(argc), false);
	ret = true;
	if (!set_rule(&rules->num_of_philos, "Number of philosophers", argv[1]))
		ret = false;
	if (!set_rule(&rules->time_to_die_ms, "Time to die", argv[2]))
		ret = false;
	if (!set_rule(&rules->time_to_eat_ms, "Time to eat", argv[3]))
		ret = false;
	if (!set_rule(&rules->time_to_sleep_ms, "Time to sleep", argv[4]))
		ret = false;
	if (argc == 6)
	{
		if (!set_rule(&rules->num_each_philo_must_eat,
				"Number of times each philosopher must eat", argv[5]))
			ret = false;
	}
	else
		rules->num_each_philo_must_eat = -1;
	return (ret);
}

static bool	set_rule(int *rule, char *target, char *arg)
{
	if (!is_number(arg))
	{
		print_invalid_arg(target, "is not a number.");
		return (false);
	}
	if (is_negative(arg))
	{
		print_invalid_arg(target, "must be positive.");
		return (false);
	}
	if (ft_isoverflow_int(arg))
	{
		print_invalid_arg(target, "is too large.");
		return (false);
	}
	*rule = ft_atoi(arg);
	return (true);
}

static bool	is_number(char *arg)
{
	if (ft_issign(*arg))
		arg++;
	if (!ft_isdigit(*arg))
		return (false);
	while (*++arg)
		if (!ft_isdigit(*arg))
			return (false);
	return (true);
}

static bool	is_negative(char *arg)
{
	if (*arg++ == '-')
	{
		while (*arg == '0')
			arg++;
		if (ft_isdigit(*arg))
			return (true);
	}
	return (false);
}
