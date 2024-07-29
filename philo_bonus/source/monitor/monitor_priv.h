/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_priv.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:37:19 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 16:28:56 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_PRIV_H
# define MONITOR_PRIV_H

# include "macros.h"
# include "monitor_pub.h"
# include "print_pub.h"
# include "typedefs.h"
# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>

void	broadcast_death(t_mon *monitor);

#endif