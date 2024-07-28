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
# include <semaphore.h>
# include <stdbool.h>

enum e_exit_codes
{
	SUCCESS			=		0,
	INPUT_ERROR		=		1,
	SEMAPHORE_FAILURE	=		2,
	MALLOC_FAILURE	=		3,
	PROCESS_FAILURE	=		4
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
	int						time_to_eat_ms;
	int						time_to_sleep_ms;
	int						num_each_philo_must_eat;
}	t_rules;

typedef struct s_semaphore_named
{
	sem_t					*sem;
	char					*name;
}	t_sem_named;

typedef struct s_semaphores
{
	t_sem_named				forks;
	t_sem_named				sync;
	t_sem_named				is_dead;
	t_sem_named				is_full;
}	t_semaphores;

typedef struct s_philo	t_philo;

struct s_philo
{
	t_philo					*base_ptr;
	pid_t					pid;
	int						id;
	const struct timeval	*start_time;
	const t_rules			*rules;
	t_state					state;
	t_semaphores			*semaphores;
	int						forks_taken;
	bool					is_outsider;
	unsigned long long		initial_think_time_us;
	unsigned long long		think_time_us;
	unsigned long long		latest_timestamp_ms;
	unsigned long long		last_meal_timestamp_ms;
	unsigned long long		meals_eaten;
	bool					is_exited;
};

#endif
