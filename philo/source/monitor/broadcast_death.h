/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast_death.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:37:19 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 06:38:01 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BROADCAST_DEATH_H
# define BROADCAST_DEATH_H

# include "philo.h"

void	broadcast_death(t_philo *philos, int num_of_philos);
void	print_death(t_philo *philos, int num_of_philos, int dead_philo);

#endif