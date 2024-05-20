/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:26:41 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/20 21:28:41 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>

// Use the following macros for time comparison:
//    void timeradd(struct timeval *a, struct timeval *b, struct timeval *res);
//    void timersub(struct timeval *a, struct timeval *b, struct timeval *res);
//    void timerclear(struct timeval *tvp);
//    int timerisset(struct timeval *tvp);
//    int timercmp(struct timeval *a, struct timeval *b, CMP);

void	set_rules(t_rules *rules)
{
	rules->number_of_philosophers = 198;
	rules->time_to_die_ms = 402;
	rules->time_to_eat_ms = 200;
	rules->time_to_sleep_ms = 200;
	rules->number_of_times_each_philosopher_must_eat = 10;
}

int	main(int argc, char *argv[])
{
	pthread_mutex_t	global_death_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	t_rules			rules;
	t_barrier		start_barrier;

	// Parse arguments
	((void)argc, (void)argv);
	// number_of_philosophers time_to_die_ms time_to_eat_ms time_to_sleep_ms [number_of_times_each_philosopher_must_eat]
	//  -> I will get global rules, and the number of philos
	// For now I can set the rules manually
	set_rules(&rules);

	if (!allocate_memory(&forks, &philos, &rules))
		return (1);

	if (!init_forks(forks, rules.number_of_philosophers))
		return (1);
	if (!init_philos(philos, forks, &rules, &start_barrier, &global_death_mutex))
		return (1);

	if (!create_philo_threads(philos, &rules))
		return (1);

	monitor(philos, rules);

	join_philo_threads(philos, &rules);
	clean(philos, forks, &rules, &global_death_mutex);
	return (0);
}
