/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pub.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:15:47 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 18:21:23 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_PUB_H
# define PRINT_PUB_H

# include "philo_pub.h"
# include <stdbool.h>
# include <sys/time.h>

/* Print Modes */
# define VERBOSE_DELAY_PRINT_THRESHOLD_US	50
# ifndef VERBOSE
#  define VERBOSE	0
# endif
# ifndef COLUMN1
#  define COLUMN1	""
# endif
# ifndef COLUMN2
#  define COLUMN2	""
# endif
# ifndef NO_COLOR
#  define NO_COLOR	0
# endif

/* Text-Style Escape Codes */
# if NO_COLOR
#  define STY_RES	""
#  define STY_BOL	""
#  define STY_RED	""
#  define STY_GRE	""
#  define STY_YEL	""
#  define STY_BLU	""
#  define STY_MAG	""
# else
#  define STY_RES	"\e[0m"
#  define STY_BOL	"\e[1m"
#  define STY_RED	"\e[31m"
#  define STY_GRE	"\e[32m"
#  define STY_YEL	"\e[33m"
#  define STY_BLU	"\e[34m"
#  define STY_MAG	"\e[35m"
# endif

/* Messages */
# if NO_COLOR
#  define MSG_FORK	"%s%llu %d has taken a fork\n"
#  define MSG_EAT	"%s%llu %d is eating\n"
#  define MSG_SLEEP	"%s%llu %d is sleeping\n"
#  define MSG_THINK	"%s%llu %d is thinking\n"
#  define MSG_DEAD	"%s%llu %d died\n"
# else
#  define MSG_FORK	"\e[1;33m%s%llu %d has taken a fork\e[0m\n"
#  define MSG_EAT	"\e[1;32m%s%llu %d is eating\e[0m\n"
#  define MSG_SLEEP	"\e[1;35m%s%llu %d is sleeping\e[0m\n"
#  define MSG_THINK	"\e[1;34m%s%llu %d is thinking\e[0m\n"
#  define MSG_DEAD	"\e[1;31m%s%llu %d died\e[0m\n"
# endif

bool	print_if_alive(t_philo *me, const char *msg);
void	print_msg(t_philo *me, const char *msg);
void	print_verbose(t_philo *me, const char *msg);
void	print_verbose_us(t_philo *me, const char *msg, unsigned long long us);
void	print_verbose_death(t_philo *me);
void	print_verbose_monitor(t_philo *philo, const char *msg);
void	print_actual_elapsed_time(
			struct timeval *start,
			unsigned long long target_time_us,
			t_philo *me);

#endif
