# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    source_files.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 22:39:40 by ldulling          #+#    #+#              #
#    Updated: 2024/07/31 18:32:28 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Main:
SRC		:=	main.c

# Initialization:
DIR		:=	init/
SRC		+=	$(addprefix $(DIR), \
            calculation.c \
            processes.c \
            t_mon.c \
            t_philos.c \
            t_semaphores.c \
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
            death.c \
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
            ft_free_and_null.c \
            ft_isdigit.c \
            ft_isoverflow_int.c \
            ft_issign.c \
            ft_isspace.c \
            ft_putstr_fd.c \
            ft_strchr.c \
            ft_strlen.c \
            ft_strncmp.c \
)
