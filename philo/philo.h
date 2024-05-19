/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:26:43 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/20 00:44:22 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <errno.h>
#include "barrier.h"

#define MSG_FORK	"has taken a fork"
#define MSG_EAT		"is eating"
#define MSG_SLEEP	"is sleeping"
#define MSG_THINK	"is thinking"
#define MSG_DEAD	"died"

#define DFLT_PRINT_DELAY_US	100

typedef struct s_rules
{
	int				number_of_philosophers;
	int				time_to_die_ms;
	int				time_to_eat_ms;
	int				time_to_sleep_ms;
	int				number_of_times_each_philosopher_must_eat;
}	t_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	const t_rules	*rules;
	t_barrier		*start_barrier;
	struct timeval	start_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	useconds_t		initial_think_us;
	struct timeval	last_meal;
	bool			is_dead;
	pthread_mutex_t is_dead_mutex;
}	t_philo;

bool	allocate_memory(pthread_mutex_t **forks, t_philo **philos, const t_rules *rules);
void	clean(t_philo *philos, pthread_mutex_t *forks, const t_rules *rules);

bool	init_forks(pthread_mutex_t *forks, int number_of_philosophers);
bool	init_philos(t_philo *philos, pthread_mutex_t *forks, const t_rules *rules, t_barrier *start_barrier);

bool	create_philo_threads(t_philo *philos, const t_rules *rules);
void	join_philo_threads(t_philo *philos, const t_rules *rules);

void	*philosopher(void *arg);

void	monitor(t_philo *philos, t_rules rules);

unsigned long long	get_timestamp(struct timeval start_time);
