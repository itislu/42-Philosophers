/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:19:21 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/04 16:47:04 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/* Timing Configuration */
# define MONITOR_INTERVAL_US				433
# define USLEEP_LONG_US						1000
# define USLEEP_SHORT_THRESHOLD_US			2000
# define USLEEP_SHORT_US					100
# define BUSY_WAIT_THRESHOLD_US				100
# define MARGIN_MS							10

/* Special Modes */
# define VERBOSE_DELAY_PRINT_THRESHOLD_US	50
# ifndef VERBOSE
#  define VERBOSE		0
# endif
# ifndef COLUMN1
#  define COLUMN1		""
# endif
# ifndef COLUMN2
#  define COLUMN2		""
# endif

/* Text-Style Escape Codes */
# if NO_COLOR
#  define STY_RES		""
#  define STY_BOL		""
#  define STY_RED		""
#  define STY_GRE		""
#  define STY_YEL		""
#  define STY_BLU		""
#  define STY_MAG		""
# else
#  define STY_RES		"\e[0m"
#  define STY_BOL		"\e[1m"
#  define STY_RED		"\e[31m"
#  define STY_GRE		"\e[32m"
#  define STY_YEL		"\e[33m"
#  define STY_BLU		"\e[34m"
#  define STY_MAG		"\e[35m"
# endif

/* Messages */
# if NO_COLOR
#  define MSG_FORK		"%s%llu %d has taken a fork\n"
#  define MSG_EAT		"%s%llu %d is eating\n"
#  define MSG_SLEEP		"%s%llu %d is sleeping\n"
#  define MSG_THINK		"%s%llu %d is thinking\n"
#  define MSG_DEAD		"%s%llu %d died\n"
# else
#  define MSG_FORK		"\e[1;33m%s%llu %d has taken a fork\e[0m\n"
#  define MSG_EAT		"\e[1;32m%s%llu %d is eating\e[0m\n"
#  define MSG_SLEEP		"\e[1;35m%s%llu %d is sleeping\e[0m\n"
#  define MSG_THINK		"\e[1;34m%s%llu %d is thinking\e[0m\n"
#  define MSG_DEAD		"\e[1;31m%s%llu %d died\e[0m\n"
# endif

/* Error Messages */
# define ERR_MUTEX		"Error: Mutex initialization failed\n"
# define ERR_MALLOC		"Error: Memory allocation failed\n"
# define ERR_THREAD		"Error: Thread creation failed\n"

#endif
