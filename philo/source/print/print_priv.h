/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_priv.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:43:08 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 17:32:24 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_PRIV_H
# define PRINT_PRIV_H

# include "philo_pub.h"
# include "print_pub.h"
# include "time_pub.h"
# include "utils_pub.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>

void	print_msg(t_philo *me, const char *msg);

#endif
