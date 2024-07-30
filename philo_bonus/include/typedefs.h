/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:19:35 by ldulling          #+#    #+#             */
/*   Updated: 2024/07/30 01:44:20 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

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
	STOPPED			=		0b100
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

/**
 * @brief Structure containing all the semaphores used in the program.
 *
 * - `forks`: Available forks.
 *
 * - `start`: To start the philosophers in sync.
 *
 * - `stop`: To stop the philosophers without exiting their processes.
 *
 * - `dead`: To signal to the monitor that a philosopher died.
 *
 * - `full`: To signal to the monitor that a philosopher got full.
 *
 * - `ready_to_exit`: To signal to the monitor that a philosopher is ready to
 *     exit.
 *     It means it won't print any more messages.
 *
 * - `exit_allowed`: To signal that a philosopher is allowed to exit.
 *     Important to allow the philosopher who died to exit before the others.
 *
 * - `mon_mutex`: To protect against race conditions in the monitor threads.
 *
 * - `print_mutex`: To protect against out of order timestamps in the outputs.
 */
typedef struct s_semaphores
{
	t_sem_named				forks;
	t_sem_named				start;
	t_sem_named				stop;
	t_sem_named				dead;
	t_sem_named				full;
	t_sem_named				ready_to_exit;
	t_sem_named				exit_allowed;
	t_sem_named				mon_mutex;
	t_sem_named				print_mutex;
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
};

typedef struct s_monitor
{
	t_philo					*philos;
	t_semaphores			*semaphores;
	const t_rules			*rules;
	bool					is_released;
}	t_mon;

#endif