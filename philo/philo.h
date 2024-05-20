/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:26:43 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/20 13:16:30 by ldulling         ###   ########.fr       */
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

/* Text-Style Escape Codes */
# define STY_RES			"\e[0m"
# define STY_BOL			"\e[1m"
# define STY_ITA			"\e[3m"
# define STY_UND			"\e[4m"
# define STY_RED			"\e[31m"
# define STY_GRE			"\e[32m"
# define STY_YEL			"\e[33m"
# define STY_BLU			"\e[34m"
# define STY_MAG			"\e[35m"
# define STY_CYA			"\e[36m"
# define STY_WHI			"\e[37m"
# define STY_GRA			"\e[90m"
# define STY_WHI_BRI		"\e[97m"
# define STY_BLA_BG			"\e[41m"
# define STY_RED_BG			"\e[41m"
# define STY_GRE_BG			"\e[42m"
# define STY_YEL_BG			"\e[43m"
# define STY_BLU_BG			"\e[44m"
# define STY_MAG_BG			"\e[45m"
# define STY_CYA_BG			"\e[46m"
# define STY_WHI_BG			"\e[47m"
# define STY_GRA_BG			"\e[100m"
# define STY_WHI_BRI_BG		"\e[107m"

# define SPACING			"                                   "

#define MSG_FORK	STY_BOL STY_YEL "%llu %d has taken a fork" STY_RES "\n"
#define MSG_EAT		STY_BOL STY_GRE "%llu %d is eating" STY_RES "\n"
#define MSG_SLEEP	STY_BOL STY_BLU "%llu %d is sleeping" STY_RES "\n"
#define MSG_THINK	STY_BOL STY_MAG "%llu %d is thinking" STY_RES "\n"
#define MSG_DEAD	STY_BOL STY_RED "%llu %d died" STY_RES "\n"

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
	useconds_t		initial_time_to_think_us;
	useconds_t		time_to_think_us;
	struct timeval	last_meal;
	bool			is_dead;
	pthread_mutex_t is_dead_mutex;
	pthread_mutex_t *global_death_mutex;
}	t_philo;

bool	allocate_memory(pthread_mutex_t **forks, t_philo **philos, const t_rules *rules);
void	clean(t_philo *philos, pthread_mutex_t *forks, const t_rules *rules, pthread_mutex_t *global_death_mutex);

bool	init_forks(pthread_mutex_t *forks, int number_of_philosophers);
bool	init_philos(t_philo *philos, pthread_mutex_t *forks, const t_rules *rules, t_barrier *start_barrier, pthread_mutex_t *global_death_mutex);

bool	create_philo_threads(t_philo *philos, const t_rules *rules);
void	join_philo_threads(t_philo *philos, const t_rules *rules);

void	*philosopher(void *arg);

void	monitor(t_philo *philos, t_rules rules);

unsigned long long	get_timestamp_ms(struct timeval start_time);
