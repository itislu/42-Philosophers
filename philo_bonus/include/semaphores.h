/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:24:17 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 18:23:55 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEMAPHORES_H
# define SEMAPHORES_H

# include <semaphore.h>

typedef struct s_semaphore_named
{
	sem_t		*sem;
	char		*name;
}	t_sem_named;

/**
 * @brief Structure containing all the semaphores used in the program.
 *
 * - `forks`: Available forks.
 *
 * - `stop`: To stop the philosophers without exiting their processes.
 *
 * - `dead`: To signal to the monitor that a philosopher died.
 *
 * - `full`: To signal to the monitor that a philosopher got full.
 *
 * - `exit_ready`: To signal to the monitor that a philosopher is ready to
 *     exit.
 *     It means the philosopher won't print any more messages.
 *
 * - `exit_allowed`: To signal that a philosopher is allowed to exit.
 *     Important to ensure the philosopher who died exits before the others.
 *
 * - `forks_mutex`: To protect against deadlocks when taking forks.
 *
 * - `mon_mutex`: To protect against race conditions in the monitor threads.
 *
 * - `philo_mutex`: To protect against race conditions in the philo threads.
 *
 * - `print_mutex`: To protect against out of order timestamps in the outputs.
 */
typedef struct s_semaphores
{
	t_sem_named	forks;
	t_sem_named	stop;
	t_sem_named	dead;
	t_sem_named	full;
	t_sem_named	exit_ready;
	t_sem_named	exit_allowed;
	t_sem_named	forks_mutex;
	t_sem_named	mon_mutex;
	t_sem_named	philo_mutex;
	t_sem_named	print_mutex;
}	t_semaphores;

#endif