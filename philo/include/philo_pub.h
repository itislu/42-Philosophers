/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pub.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:10:55 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 17:45:02 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PUB_H
# define PHILO_PUB_H

# include "rules_pub.h"
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef enum e_state
{
	ALIVE			=		0b0000,
	FULL			=		0b0001,
	DEAD			=		0b0010,
	STOPPED			=		0b0100,
	CONFIRMED		=		0b1000
}	t_state;

typedef struct s_philo
{
	pthread_t				thread;
	int						id;
	const struct timeval	*start_time;
	const t_rules			*rules;
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
	unsigned long long		initial_think_time_us;
	unsigned long long		think_time_us;
	struct timeval			cycle_target_time;
	unsigned long long		initial_cycle_time_us;
	unsigned long long		cycle_time_us;
	unsigned long long		latest_timestamp_ms;
	unsigned long long		last_meal_timestamp_ms;
	unsigned long long		meals_eaten;
}	t_philo;

void	*philosopher(void *arg);
bool	take_forks_left_first(t_philo *me);
bool	take_forks_right_first(t_philo *me);
void	release_forks_left_first(t_philo *me);
void	release_forks_right_first(t_philo *me);
bool	check_alive(t_philo *me);

#endif
