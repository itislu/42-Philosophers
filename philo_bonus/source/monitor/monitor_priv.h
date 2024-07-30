/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_priv.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:37:19 by ldulling          #+#    #+#             */
/*   Updated: 2024/07/30 01:38:41 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_PRIV_H
# define MONITOR_PRIV_H

# include "macros.h"
# include "print_pub.h"
# include "typedefs.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <sys/wait.h>

void	broadcast_death(t_mon *monitor);

#endif