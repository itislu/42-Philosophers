/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:26:41 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 18:18:57 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_pub.h"
#include "monitor_pub.h"
#include "philo_pub.h"
#include "rules_pub.h"
#include "semaphores.h"
#include "utils_pub.h"
#include <sys/time.h>

int	main(int argc, char *argv[])
{
	struct timeval	start_time;
	t_rules			rules;
	t_semaphores	semaphores;
	t_philo			*philos;
	t_mon			monitor_data;

	if (!parse_rules(&rules, argc, argv))
		return (INPUT_ERROR);
	if (rules.num_of_philos == 0 || rules.num_each_philo_must_eat == 0)
		return (print_nothing_to_do(&rules), SUCCESS);
	if (!init_semaphores(&semaphores, rules.num_of_philos))
		return (ft_putstr_fd(ERR_SEMAPHORE, STDERR_FILENO), SEMAPHORE_FAILURE);
	if (!init_philos(&philos, &semaphores, &rules, &start_time))
		return (cleanup(philos, &semaphores, ERR_MALLOC), MALLOC_FAILURE);
	init_monitor(&monitor_data, philos, &semaphores, &rules);
	gettimeofday(&start_time, NULL);
	if (!create_philo_processes(philos, rules.num_of_philos))
		return (cleanup(philos, &semaphores, ERR_PROCESS), PROCESS_FAILURE);
	if (!monitor(&monitor_data))
		return (cleanup(philos, &semaphores, ERR_THREAD), THREAD_FAILURE);
	cleanup(philos, &semaphores, NULL);
	return (SUCCESS);
}
