/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pub.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:10:55 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/11 08:50:34 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PUB_H
# define PHILO_PUB_H

# include "typedefs.h"
# include <stdbool.h>

void	philosopher(t_philo *me);
bool	take_forks(t_philo *me);
void	release_forks(t_philo *me);
bool	check_alive(t_philo *me);

#endif
