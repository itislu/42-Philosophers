/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_priv.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:37:19 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 17:36:43 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_PRIV_H
# define MONITOR_PRIV_H

# include "init_pub.h"
# include "monitor_pub.h"
# include "print_pub.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <sys/wait.h>

bool	broadcast_death(t_mon *monitor);

#endif