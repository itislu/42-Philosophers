# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    source_files.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 22:39:40 by ldulling          #+#    #+#              #
#    Updated: 2024/08/07 17:28:52 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Main:
SRC		:=	main.c

# Initialization:
DIR		:=	init/
SRC		+=	$(addprefix $(DIR), \
            calculation.c \
            margin.c \
            monitor_data.c \
            philo_data.c \
            processes.c \
            semaphores.c \
)

# Monitor Process:
DIR		:=	monitor/
SRC		+=	$(addprefix $(DIR), \
            broadcast.c \
            monitor.c \
)

# Philosopher Processes:
DIR		:=	philosopher/
SRC		+=	$(addprefix $(DIR), \
            forks.c \
            philo.c \
            philo_action.c \
            status.c \
            usleep.c \
)

# Printing:
DIR		:=	print/
SRC		+=	$(addprefix $(DIR), \
            print.c \
            verbose.c \
)

# Simulation Rules:
DIR		:=	rules/
SRC		+=	$(addprefix $(DIR), \
            feedback.c \
            rules.c \
)

# Time:
DIR		:=	time/
SRC		+=	$(addprefix $(DIR), \
            time.c \
)

# Utils:
DIR		:=	utils/
SRC		+=	$(addprefix $(DIR), \
            ft_atoi.c \
            ft_free_and_null.c \
            ft_isdigit.c \
            ft_iseven.c \
            ft_isoverflow_int.c \
            ft_issign.c \
            ft_isspace.c \
            ft_max.c \
            ft_putstr_fd.c \
            ft_round_down_even.c \
            ft_strchr.c \
            ft_strlen.c \
            ft_strncmp.c \
)
