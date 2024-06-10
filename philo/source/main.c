/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:26:41 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 11:03:25 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"
#include "input.h"
#include "init.h"
#include "typedefs.h"
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

int	main(int argc, char *argv[])
{
	struct timeval	start_time;
	t_mutexes		mutexes;
	t_philo			*philos;
	t_rules			rules;

	if (!parse_rules(&rules, argc, argv))
		return (1);
	if (rules.num_of_philos == 0 || rules.num_each_philo_must_eat == 0)
		return (print_nothing_to_do(&rules), 0);
	if (!init_mutexes(&mutexes, &rules))
		return (2);
	if (!init_philos(&philos, &mutexes, &rules, &start_time))
		return (destroy_mutexes(&mutexes, &rules), free(philos), 3);
	pthread_mutex_lock(mutexes.sync_mutex);
	if (!create_philo_threads(philos, &rules))
		return (destroy_mutexes(&mutexes, &rules), free(philos), 4);
	gettimeofday(&start_time, NULL);
	pthread_mutex_unlock(mutexes.sync_mutex);
	monitor(philos, rules);
	join_philo_threads(philos, rules.num_of_philos);
	destroy_mutexes(&mutexes, &rules);
	free(philos);
	return (0);
}
