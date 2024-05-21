/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:07:48 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/21 19:27:12 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils/utils.h"

void	report_wrong_arg_num(int argc)
{
	ft_putstr_fd("Error: Wrong number of arguments\n", STDERR_FILENO);

	if (argc < 2)
		ft_putstr_fd("  - Number of philosophers is missing\n", STDERR_FILENO);
	if (argc < 3)
		ft_putstr_fd("  - Time to die is missing\n", STDERR_FILENO);
	if (argc < 4)
		ft_putstr_fd("  - Time to eat is missing\n", STDERR_FILENO);
	if (argc < 5)
		ft_putstr_fd("  - Time to sleep is missing\n", STDERR_FILENO);
	ft_putstr_fd("  - Optional: Number of times each philosopher must eat\n", STDERR_FILENO);
	ft_putstr_fd("\nUsage: ./philo number_of_philosophers time_to_die_in_ms time_to_eat_in_ms time_to_sleep_in_ms [number_of_times_each_philosopher_must_eat]\n", STDERR_FILENO);
	ft_putstr_fd("Example: ./philo 5 610 200 200\n", STDERR_FILENO);
}

bool	is_number(char *arg)
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

bool	is_negative(char *arg)
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

void	print_invalid_arg(char *target, char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(target, STDERR_FILENO);
	ft_putstr_fd(" ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

bool	set_rule(int *rule, char *target, char *arg)
{
	if (!is_number(arg))
	{
		print_invalid_arg(target, "is not a number");
		return (false);
	}
	if (is_negative(arg))
	{
		print_invalid_arg(target, "must be positive");
		return (false);
	}
	if (ft_isoverflow_int(arg))
	{
		print_invalid_arg(target, "is too large");
		return (false);
	}
	*rule = ft_atoi(arg);
	return (true);
}

bool	parse_rules(t_rules *rules, int argc, char *argv[])
{
	bool	ret;

	if (argc != 5 && argc != 6)
		return (report_wrong_arg_num(argc), false);

	// Number of philosophers
		// 0 does nothing
	ret = true;
	if (!set_rule(&rules->number_of_philosophers, "Number of philosophers", argv[1]))
		ret = false;

	// Time to die
		// 0 does nothing
	if (!set_rule(&rules->time_to_die_ms, "Time to die", argv[2]))
		ret = false;

	// Time to eat
	if (!set_rule(&rules->time_to_eat_ms, "Time to eat", argv[3]))
		ret = false;

	// Time to sleep
	if (!set_rule(&rules->time_to_sleep_ms, "Time to sleep", argv[4]))
		ret = false;

	// Number of times each philosopher must eat
		// Optional
	if (argc == 6)
	{
		if (!set_rule(&rules->number_of_times_each_philosopher_must_eat, "Number of times each philosopher must eat", argv[5]))
			ret = false;
	}
	else
		rules->number_of_times_each_philosopher_must_eat = -1;
	return (ret);
}
