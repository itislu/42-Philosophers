/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:19:35 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/11 10:38:17 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include <pthread.h>
# include <stdbool.h>

enum e_exit_codes
{
	SUCCESS			=		0,
	INPUT_ERROR		=		1,
	MUTEX_FAILURE	=		2,
	MALLOC_FAILURE	=		3,
	THREAD_FAILURE	=		4
};

typedef enum e_state
{
	ALIVE			=		0b000,
	FULL			=		0b001,
	DEAD			=		0b010,
	CONFIRMED		=		0b100
}	t_state;

typedef struct s_rules
{
	int						num_of_philos;
	int						time_to_die_ms;
	unsigned long long		time_to_die_us;
	int						time_to_eat_ms;
	int						time_to_sleep_ms;
	int						num_each_philo_must_eat;
}	t_rules;

typedef struct s_mutexes
{
	pthread_mutex_t			*forks;
	pthread_mutex_t			*state_mutexes;
	pthread_mutex_t			*sync_mutex;
	pthread_mutex_t			*print_mutex;
}	t_mutexes;

typedef struct s_philo
{
	pthread_t				thread;
	int						id;
	struct timeval const	*start_time;
	t_state					state;
	pthread_mutex_t			*state_mutex;
	pthread_mutex_t			*sync_mutex;
	pthread_mutex_t			*print_mutex;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	bool					locked_left_fork;
	bool					locked_right_fork;
	bool					(*take_forks)(struct s_philo * me);
	void					(*release_forks)(struct s_philo *me);
	bool					is_outsider;
	unsigned int			initial_thinking_time_us;
	unsigned int			thinking_time_us;
	unsigned long long		latest_timestamp_ms;
	unsigned long long		last_meal_timestamp_ms;
	unsigned long long		meals_eaten;
	t_rules const			*rules;
}	t_philo;

#endif
