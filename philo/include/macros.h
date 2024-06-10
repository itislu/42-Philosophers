/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:19:21 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 10:20:51 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# ifndef VERBOSE
#  define VERBOSE 0
# endif

# ifndef COLUMN1
#  define COLUMN1			""
# endif
# ifndef COLUMN2
#  define COLUMN2			""
# endif
# ifndef COLUMN3
#  define COLUMN3			""
# endif

/* Text-Style Escape Codes */
# define STY_RES			"\e[0m"
# define STY_BOL			"\e[1m"
# define STY_ITA			"\e[3m"
# define STY_UND			"\e[4m"
# define STY_RED			"\e[31m"
# define STY_GRE			"\e[32m"
# define STY_YEL			"\e[33m"
# define STY_BLU			"\e[34m"
# define STY_MAG			"\e[35m"
# define STY_CYA			"\e[36m"
# define STY_WHI			"\e[37m"
# define STY_GRA			"\e[90m"
# define STY_WHI_BRI		"\e[97m"
# define STY_BLA_BG			"\e[41m"
# define STY_RED_BG			"\e[41m"
# define STY_GRE_BG			"\e[42m"
# define STY_YEL_BG			"\e[43m"
# define STY_BLU_BG			"\e[44m"
# define STY_MAG_BG			"\e[45m"
# define STY_CYA_BG			"\e[46m"
# define STY_WHI_BG			"\e[47m"
# define STY_GRA_BG			"\e[100m"
# define STY_WHI_BRI_BG		"\e[107m"

# define MSG_FORK			"\e[1;33m%s%llu %d has taken a fork\e[0m\n"
# define MSG_EAT			"\e[1;32m%s%llu %d is eating\e[0m\n"
# define MSG_SLEEP			"\e[1;35m%s%llu %d is sleeping\e[0m\n"
# define MSG_THINK			"\e[1;34m%s%llu %d is thinking\e[0m\n"
# define MSG_DEAD			"\e[1;31m%s%llu %d died\e[0m\n"

# define VERBOSE_USLEEP_DELAY_THRESHOLD_US	50

# define MONITOR_INTERVAL_US		100
# define USLEEP_LONG_US				1000
# define USLEEP_SHORT_THRESHOLD_US	2000
# define USLEEP_SHORT_US			100
# define BUSY_WAIT_THRESHOLD_US		100
# define MARGIN_MS					10

// It's possible to do these with a static struct in a function and access immediately, like func().func_ptr
# define LONG_THINKING_TIME_US		(me->rules->time_to_eat_ms * 2 - me->rules->time_to_sleep_ms - 5)
# define SHORT_THINKING_TIME_US		(me->rules->time_to_eat_ms - me->rules->time_to_sleep_ms - 5)
# define IS_EVEN					% 2 == 0
# define IS_ODD						% 2 == 1

#endif
