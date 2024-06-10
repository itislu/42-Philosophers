# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    source_files.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 22:39:40 by ldulling          #+#    #+#              #
#    Updated: 2024/06/10 05:21:59 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Main:
SRC		:=	main.c

# Initialization:
DIR		:=	init/
SRC		+=	$(addprefix $(DIR), \
            calculate.c \
            create_threads.c \
            init_mutexes.c \
            init_philos.c \
)

# User input:
DIR		:=	input/
SRC		+=	$(addprefix $(DIR), \
            feedback.c \
            parsing.c \
)

# Monitor Thread:
DIR		:=	monitor/
SRC		+=	$(addprefix $(DIR), \
            monitor.c \
)

# Philosopher Threads:
DIR		:=	philosopher/
SRC		+=	$(addprefix $(DIR), \
            forks.c \
            philo.c \
            philo_eat.c \
            philo_sleep.c \
            philo_think.c \
            status.c \
            usleep.c \
)

# Printing:
DIR		:=	print/
SRC		+=	$(addprefix $(DIR), \
            print.c \
            verbose.c \
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
            ft_isdigit.c \
            ft_isoverflow_int.c \
            ft_issign.c \
            ft_isspace.c \
            ft_putstr_fd.c \
            ft_strchr.c \
            ft_strlen.c \
            ft_strncmp.c \
)
