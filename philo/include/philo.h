/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:26:43 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 06:40:47 by ldulling         ###   ########.fr       */
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
#include <stddef.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>

# ifndef VERBOSE
#  define VERBOSE 0
# endif

# ifndef COLUMN1
#  define COLUMN1			""
# endif
# ifndef COLUMN2
#  define COLUMN2			""
# endif
# ifndef COLUMN3
#  define COLUMN3			""
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

#define MSG_FORK			"\e[1;33m%s%llu %d has taken a fork\e[0m\n"
#define MSG_EAT				"\e[1;32m%s%llu %d is eating\e[0m\n"
#define MSG_SLEEP			"\e[1;35m%s%llu %d is sleeping\e[0m\n"
#define MSG_THINK			"\e[1;34m%s%llu %d is thinking\e[0m\n"
#define MSG_DEAD			"\e[1;31m%s%llu %d died\e[0m\n"

#define VERBOSE_USLEEP_DELAY_THRESHOLD_US	50

#define MONITOR_INTERVAL_US			100
#define USLEEP_LONG_US				1000
#define USLEEP_SHORT_THRESHOLD_US	2000
#define USLEEP_SHORT_US				100
#define BUSY_WAIT_THRESHOLD_US		100
#define MARGIN_MS					10

// It's possible to do these with a static struct in a function and access immediately, like func().func_ptr
#define LONG_THINKING_TIME_US		(me->rules->time_to_eat_ms * 2 - me->rules->time_to_sleep_ms - 5)
#define SHORT_THINKING_TIME_US		(me->rules->time_to_eat_ms - me->rules->time_to_sleep_ms - 5)
#define IS_EVEN						% 2 == 0
#define IS_ODD						% 2 == 1

typedef enum e_state
{
	ALIVE		= 0b000,
	FULL		= 0b001,
	DEAD		= 0b010,
	CONFIRMED	= 0b100
}	t_state;

typedef struct s_rules
{
	int					num_of_philos;
	int					time_to_die_ms;
	unsigned long long	time_to_die_us;
	int					time_to_eat_ms;
	int					time_to_sleep_ms;
	int					num_each_philo_must_eat;
}	t_rules;

typedef struct s_mutexes
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*state_mutexes;
	pthread_mutex_t	*sync_mutex;
	pthread_mutex_t	*print_mutex;
}	t_mutexes;

typedef struct s_philo
{
	pthread_t				thread;
	int						id;
	struct timeval const	*start_time;
	t_state					state;
	pthread_mutex_t 		*state_mutex;
	pthread_mutex_t 		*sync_mutex;
	pthread_mutex_t			*print_mutex;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	bool					locked_left_fork;
	bool					locked_right_fork;
	bool					(*take_forks)(struct s_philo *me);
	void					(*release_forks)(struct s_philo *me);
	bool					is_outsider;
	unsigned int			initial_thinking_time_us;
	unsigned int			thinking_time_us;
	unsigned long long		latest_timestamp;
	unsigned long long		last_meal_timestamp;
	unsigned long long		meals_eaten;
	t_rules const			*rules;
}	t_philo;

bool	parse_rules(t_rules *rules, int argc, char *argv[]);

bool	init_mutexes(t_mutexes *mutexes, t_rules *rules);
void	destroy_mutexes(t_mutexes *mutexes, t_rules *rules);
bool	init_philos(t_philo **philos, t_mutexes *mutexes, const t_rules *rules, struct timeval *start_time);

bool	take_forks_left_first(t_philo *me);
bool	take_forks_right_first(t_philo *me);
void	release_forks_left_first(t_philo *me);
void	release_forks_right_first(t_philo *me);

bool	create_philo_threads(t_philo *philos, const t_rules *rules);
void	join_philo_threads(t_philo *philos, int count);

void	*philosopher(void *arg);

bool	philo_eat(t_philo *me);
bool	philo_sleep(t_philo *me);
bool	philo_think(t_philo *me, unsigned int thinking_time_us);
bool	philo_think_initial(t_philo *me, unsigned int thinking_time_us);

void	broadcast_death(t_philo *philos, int num_of_philos);
void	monitor(t_philo *philos, t_rules rules);

unsigned long long	get_elapsed_time_ms(struct timeval *start_time);
unsigned long long	get_elapsed_time_us(struct timeval *start_time);

void	print_nothing_to_do(t_rules *rules);
bool	print_if_alive(t_philo *me, const char *msg);
bool	check_alive(t_philo *me);
void	print_msg(t_philo *me, const char *msg);
void	print_verbose(t_philo *me, const char *msg);
void	print_verbose_death(t_philo *me);

bool	usleep_while_alive(unsigned int us, t_philo *philo);
bool	usleep_while_alive_precise(unsigned int us, t_philo *philo);

void	print_actual_elapsed_time(struct timeval *start, struct timeval *end, unsigned int target_time_us, t_philo *philo);

#endif
