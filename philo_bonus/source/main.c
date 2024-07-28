/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:26:41 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 16:39:36 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_pub.h"
#include "input_pub.h"
#include "macros.h"
#include "monitor_pub.h"
#include "typedefs.h"
#include "utils_pub.h"
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	struct timeval	start_time;
	t_semaphores	semaphores;
	t_philo			*philos;
	t_rules			rules;

	if (!parse_rules(&rules, argc, argv))
		return (INPUT_ERROR);
	if (rules.num_of_philos == 0 || rules.num_each_philo_must_eat == 0)
		return (print_nothing_to_do(&rules), 0);
	if (!init_semaphores(&semaphores, rules.num_of_philos))
		return (ft_putstr_fd(ERR_SEMAPHORE, STDERR_FILENO), SEMAPHORE_FAILURE);
	if (!init_philos(&philos, &semaphores, &rules, &start_time))
		return (cleanup(philos, &semaphores, ERR_MALLOC), MALLOC_FAILURE);
	gettimeofday(&start_time, NULL);
	if (!create_philo_processes(philos, rules.num_of_philos))
		return (cleanup(philos, &semaphores, ERR_PROCESS), PROCESS_FAILURE);
	sem_post(semaphores.start.sem);
	monitor(philos);
	cleanup(philos, &semaphores, NULL);
	return (SUCCESS);
}
