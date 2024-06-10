/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pub_philo.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:10:55 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 10:44:07 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUB_PHILO_H
# define PUB_PHILO_H

# include "typedefs.h"
# include <stdbool.h>

void	*philosopher(void *arg);
bool	take_forks_left_first(t_philo *me);
bool	take_forks_right_first(t_philo *me);
void	release_forks_left_first(t_philo *me);
void	release_forks_right_first(t_philo *me);
bool	check_alive(t_philo *me);

#endif
