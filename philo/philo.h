/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:26:43 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/25 16:02:25 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include "barrier.h"

# ifndef __useconds_t_defined
typedef __useconds_t useconds_t;
# endif

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

#define DFLT_PRINT_DELAY_US			0

#define USLEEP_LONG_US				1000
#define USLEEP_SHORT_THRESHOLD_US	2000
#define USLEEP_SHORT_US				100
#define BUSY_WAIT_THRESHOLD_US		100

typedef enum e_state
{
	ALIVE	= 0b000,
	FULL	= 0b001,
	DYING	= 0b010,
	DEAD	= 0b100
}	t_state;

typedef struct s_rules
{
	int					number_of_philosophers;
	int					time_to_die_ms;
	unsigned long long	time_to_die_us;
	int					time_to_eat_ms;
	int					time_to_sleep_ms;
	int					number_of_times_each_philosopher_must_eat;
}	t_rules;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	const t_rules	*rules;
	t_barrier		*start_barrier;
	pthread_mutex_t *start_mutex;
	struct timeval	*start_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	bool			locked_left_fork;
	bool			locked_right_fork;
	useconds_t		initial_time_to_think_us;
	useconds_t		time_to_think_us;
	struct timeval	last_meal_time;
	int				meals_remaining;
	pthread_mutex_t state_mutex;
	t_state			state;
}	t_philo;

bool	parse_rules(t_rules *rules, int argc, char *argv[]);

bool	allocate_memory(pthread_mutex_t **forks, t_philo **philos, const t_rules *rules);
void	clean(t_philo *philos, pthread_mutex_t *forks, const t_rules *rules, pthread_mutex_t *start_mutex);

bool	init_forks(pthread_mutex_t *forks, int number_of_philosophers);
bool	init_philos(t_philo *philos, pthread_mutex_t *forks, const t_rules *rules, t_barrier *start_barrier, pthread_mutex_t *start_mutex, struct timeval *start_time);

bool	create_philo_threads(t_philo *philos, const t_rules *rules);
void	join_philo_threads(t_philo *philos, const t_rules *rules);

void	*philosopher(void *arg);

void	monitor(t_philo *philos, t_rules rules);

unsigned long long	get_elapsed_time_ms(struct timeval *start_time);
unsigned long long	get_elapsed_time_us(struct timeval *start_time);

bool	print_if_alive(t_philo *me, useconds_t print_delay, const char *msg);
bool	check_alive(t_philo *me);
void	print_msg(t_philo *me, const char *msg);
void	print_db(t_philo *me, const char *msg);
void	print_db_death(t_philo *me);

bool	usleep_while_alive(useconds_t us, t_philo *philo);

void	print_actual_slept_time(struct timeval *start, struct timeval *end, useconds_t us, t_philo *philo);

#endif
