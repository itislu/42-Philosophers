/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:26:41 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 17:10:58 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_pub.h"
#include "monitor_pub.h"
#include "mutexes.h"
#include "philo_pub.h"
#include "rules_pub.h"
#include "utils_pub.h"
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

int	main(int argc, char *argv[])
{
	struct timeval	start_time;
	t_rules			rules;
	t_mutexes		mutexes;
	t_philo			*philos;

	if (!parse_rules(&rules, argc, argv))
		return (INPUT_ERROR);
	if (rules.num_of_philos == 0 || rules.num_each_philo_must_eat == 0)
		return (print_nothing_to_do(&rules), SUCCESS);
	if (!init_mutexes(&mutexes, rules.num_of_philos))
		return (ft_putstr_fd(ERR_MUTEX, STDERR_FILENO), MUTEX_FAILURE);
	if (!init_philos(&philos, &mutexes, &rules, &start_time))
		return (destroy_mutexes(&mutexes, rules.num_of_philos), free(philos),
			ft_putstr_fd(ERR_MALLOC, STDERR_FILENO), MALLOC_FAILURE);
	pthread_mutex_lock(mutexes.sync_mutex);
	if (!create_philo_threads(philos, rules.num_of_philos))
		return (destroy_mutexes(&mutexes, rules.num_of_philos), free(philos),
			ft_putstr_fd(ERR_THREAD, STDERR_FILENO), THREAD_FAILURE);
	gettimeofday(&start_time, NULL);
	pthread_mutex_unlock(mutexes.sync_mutex);
	monitor(philos, &rules);
	join_philo_threads(philos, rules.num_of_philos);
	destroy_mutexes(&mutexes, rules.num_of_philos);
	free(philos);
	return (SUCCESS);
}
