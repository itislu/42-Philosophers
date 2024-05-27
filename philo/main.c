/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:26:41 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/27 01:20:25 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Use the following macros for time comparison:
//    void timeradd(struct timeval *a, struct timeval *b, struct timeval *res);
//    void timersub(struct timeval *a, struct timeval *b, struct timeval *res);
//    void timerclear(struct timeval *tvp);
//    int timerisset(struct timeval *tvp);
//    int timercmp(struct timeval *a, struct timeval *b, CMP);

int	main(int argc, char *argv[])
{
	struct timeval	start_time;
	pthread_mutex_t	sync_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	t_rules			rules;

	if (!parse_rules(&rules, argc, argv))
		return (1);

	if (!allocate_memory(&forks, &philos, &rules))
		return (2);

	if (!init_mutexes(forks, rules.number_of_philosophers, sizeof(pthread_mutex_t), 0))
		return (free_memory(forks, philos), 3);
	if (!init_philos(philos, forks, &rules, &sync_mutex, &start_time))
		return (destroy_mutexes(forks, rules.number_of_philosophers, sizeof(pthread_mutex_t), 0), free_memory(forks, philos), 4);

	pthread_mutex_lock(&sync_mutex);
	if (!create_philo_threads(philos, &rules))
		return (clean(philos, forks, &rules, &sync_mutex), 5);
	gettimeofday(&start_time, NULL);
	pthread_mutex_unlock(&sync_mutex);
	monitor(philos, rules);

	join_philo_threads(philos, rules.number_of_philosophers);
	clean(philos, forks, &rules, &sync_mutex);
	return (0);
}
