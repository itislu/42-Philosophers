/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_priv.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:43:08 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 16:36:23 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_PRIV_H
# define PRINT_PRIV_H

# include "macros.h"
# include "philo_pub.h"
# include "time_pub.h"
# include "typedefs.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

void	print_msg(t_philo *me, const char *msg);

#endif
