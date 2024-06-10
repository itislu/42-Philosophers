/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast_death.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:37:19 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 05:47:00 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BROADCAST_DEATH_H
# define BROADCAST_DEATH_H

# include "philo.h"

void	broadcast_death(t_philo *philos, int number_of_philosophers);
void	print_death(
			t_philo *philos, int number_of_philosophers, int dead_philo);

#endif