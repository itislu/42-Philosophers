# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    source_files.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 22:39:40 by ldulling          #+#    #+#              #
#    Updated: 2024/05/19 22:41:38 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Initialize SRC
SRC		:= $(SRC)

# Main:
DIR		:=	./
SRC		+=	$(addprefix $(DIR), \
            main.c \
            allocate.c \
            barrier.c \
            eat.c \
            init.c \
            monitor.c \
            philo.c \
            sleep.c \
            think.c \
            threads.c \
            time.c \
)
