/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priv_philo.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:09:47 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 10:44:07 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIV_PHILO_H
# define PRIV_PHILO_H

# include "typedefs.h"
# include <stdbool.h>

bool	philo_eat(t_philo *me);
bool	philo_sleep(t_philo *me);
bool	philo_think(t_philo *me, unsigned int thinking_time_us);
bool	philo_think_initial(t_philo *me, unsigned int thinking_time_us);
bool	usleep_while_alive(unsigned int us, t_philo *philo);
bool	usleep_while_alive_precise(unsigned int us, t_philo *philo);

#endif
