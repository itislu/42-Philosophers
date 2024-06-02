/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:26:41 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/02 23:58:35 by ldulling         ###   ########.fr       */
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
	t_mutexes		mutexes;
	t_philo			*philos;
	t_rules			rules;

	if (!parse_rules(&rules, argc, argv))
		return (1);
	if (rules.number_of_philosophers == 0 || rules.number_of_times_each_philosopher_must_eat == 0)
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

	join_philo_threads(philos, rules.number_of_philosophers);
	destroy_mutexes(&mutexes, &rules);
	free(philos);
	return (0);
}
