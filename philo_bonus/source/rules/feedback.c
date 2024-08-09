/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feedback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 04:40:10 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 15:26:58 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rules_priv.h"

void	print_nothing_to_do(t_rules *rules)
{
	if (rules->num_of_philos == 0)
		printf("No philosophers at the table.\n");
	if (rules->num_each_philo_must_eat == 0)
		printf("No one should eat.\n");
}

void	print_wrong_arg_num(int argc)
{
	ft_putstr_fd("Input error: Wrong number of arguments.\n", STDERR_FILENO);
	if (argc < 2)
		ft_putstr_fd("  - Number of philosophers is missing.\n", STDERR_FILENO);
	if (argc < 3)
		ft_putstr_fd("  - Time to die is missing.\n", STDERR_FILENO);
	if (argc < 4)
		ft_putstr_fd("  - Time to eat is missing.\n", STDERR_FILENO);
	if (argc < 5)
		ft_putstr_fd("  - Time to sleep is missing.\n", STDERR_FILENO);
	ft_putstr_fd("  - Optional: Number of times each philosopher must eat.\n",
		STDERR_FILENO);
	ft_putstr_fd("\nUsage: ./philo ", STDERR_FILENO);
	ft_putstr_fd("number_of_philosophers ", STDERR_FILENO);
	ft_putstr_fd("time_to_die_in_ms ", STDERR_FILENO);
	ft_putstr_fd("time_to_eat_in_ms ", STDERR_FILENO);
	ft_putstr_fd("time_to_sleep_in_ms ", STDERR_FILENO);
	ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n",
		STDERR_FILENO);
	ft_putstr_fd("Example: ./philo 5 610 200 200\n", STDERR_FILENO);
}

void	print_invalid_arg(char *target, char *msg)
{
	ft_putstr_fd("Input error: ", STDERR_FILENO);
	ft_putstr_fd(target, STDERR_FILENO);
	ft_putstr_fd(" ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
