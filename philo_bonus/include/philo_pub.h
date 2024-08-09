/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pub.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:10:55 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 17:27:05 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PUB_H
# define PHILO_PUB_H

# include "rules_pub.h"
# include "semaphores.h"
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
struct s_philo
{
	t_philo					*base_ptr;
	pid_t					pid;
	int						id;
	const struct timeval	*start_time;
	const t_rules			*rules;
	t_semaphores			*semaphores;
	int						forks_taken;
	bool					is_stopped;
	bool					is_dead;
	unsigned long long		initial_think_time_us;
	unsigned long long		think_time_us;
	struct timeval			cycle_target_time;
	unsigned long long		initial_cycle_time_us;
	unsigned long long		cycle_time_us;
	unsigned long long		latest_timestamp_ms;
	unsigned long long		last_meal_timestamp_ms;
	unsigned long long		meals_eaten;
};

void	philosopher(t_philo *me);
bool	take_forks(t_philo *me);
void	release_forks(t_philo *me);
bool	check_alive(t_philo *me);

#endif
