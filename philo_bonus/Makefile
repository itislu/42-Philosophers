# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 22:39:28 by ldulling          #+#    #+#              #
#    Updated: 2024/07/30 17:49:31 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ***************************** CONFIGURATION ******************************** #

#	Executable

NAME 			:=	philo_bonus


#	Directories

SRC_DIR			:=	source
INC_DIR			:=	include
BUILD_DIR		:=	build
OBJ_DIR			:=	$(BUILD_DIR)/_obj
DEP_DIR			:=	$(BUILD_DIR)/_dep


#	Dependencies

BUILDFILES		:=	Makefile \
					$(BUILD_DIR)/source_files.mk


#	Flags

CC 				:=	cc
CC_VERSION		:=	$(shell $(CC) --version | head -1)
CFLAGS 			:=	-Wall -Wextra -Werror -ggdb3 -pthread# -fsanitize=thread
INCFLAGS 		:=	$(addprefix -I,$(INC_DIR))
MAKEFLAGS		:=	-j -s


#	Macro definitions

COLUMN1			:=	'""'
COLUMN2			:=	'"                                   "'
COLUMN3			:=	'"                                                                      "'

export				MACROS
ifneq (,$(filter verbose%,$(MAKECMDGOALS)))
MACROS			:=	-D VERBOSE=1
endif
ifneq (,$(filter verbose1 column1,$(MAKECMDGOALS)))
MACROS			+=	-D COLUMN1='"$(COLUMN1)"' \
					-D COLUMN2='"$(COLUMN1)"' \
					-D COLUMN3='"$(COLUMN1)"'
else ifneq (,$(filter verbose2 column2,$(MAKECMDGOALS)))
MACROS			+=	-D COLUMN1='"$(COLUMN1)"' \
					-D COLUMN2='"$(COLUMN2)"' \
					-D COLUMN3='"$(COLUMN2)"'
else ifneq (,$(filter verbose3 column3,$(MAKECMDGOALS)))
MACROS			+=	-D COLUMN1='"$(COLUMN1)"' \
					-D COLUMN2='"$(COLUMN2)"' \
					-D COLUMN3='"$(COLUMN3)"'
endif
ifneq (,$(filter nocolor,$(MAKECMDGOALS)))
MACROS			+=	-D NO_COLOR=1
endif


#	Valgrind

VALGRIND		:=	$(shell which valgrind)

VALGRINDFLAGS	=	--errors-for-leak-kinds=all \
					--leak-check=full \
					--read-var-info=yes \
					--show-error-list=yes \
					--show-leak-kinds=all \
					--track-origins=yes \
					--trace-children=yes


#	Terminal

TERMINAL		:=	$(shell which gnome-terminal 2> /dev/null)

ifeq ($(filter val,$(MAKECMDGOALS)),val)
TERMINALTITLE	:=	valgrind $(NAME)
else ifeq ($(filter valfd,$(MAKECMDGOALS)),valfd)
TERMINALTITLE	:=	valgrind-fd $(NAME)
else
TERMINALTITLE	:=	$(NAME)
endif

TERMINALFLAGS	:=	--title="$(TERMINALTITLE)" -- /bin/sh -c


#	Files

include				$(BUILD_DIR)/source_files.mk
OBJ 			:=	$(SRC:%.c=$(OBJ_DIR)/%.o)
DEP				:=	$(SRC:%.c=$(DEP_DIR)/%.d)


#	Subdirectories

OBJ_SUBDIRS		:=	$(sort $(dir $(OBJ)))
DEP_SUBDIRS		:=	$(sort $(dir $(DEP)))


# ***************************** BUILD PROCESS ******************************** #

.PHONY			:	all verbose verbose1 verbose2 verbose3 column1 column2 column3 nocolor \
					run val clear clean fclean ffclean re


#	Compilation

all				:
					if $(MAKE) --question $(NAME); then \
						echo $(MSG_NO_CHNG); \
					else \
						echo -n $(MSG_INFO)$(MSG_START); \
						if $(MAKE) $(NAME); then \
							echo $(MSG_SUCCESS); \
						else \
							echo $(MSG_FAILURE); \
							exit 42; \
						fi; \
					fi

verbose	verbose1 verbose2 verbose3 column1 column2 column3 nocolor:
					echo -n $(MSG_MODE)
					echo -n $(MSG_COLUMN)
					$(MAKE) re
					$(MAKE) clean

run				:	all
					"./$(NAME)" $(ARGS)

val				:	all
					$(VALGRIND) $(VALGRINDFLAGS) "./$(NAME)" $(ARGS)

clear			:
					clear
					$(MAKE) all


#	Executable linking

$(NAME)			:	$(LIBRARIES) $(OBJ)
					$(CC) $(CFLAGS) $(INCFLAGS) $(OBJ) $(LIBFLAGS) -o $(NAME)


#	Source file compiling

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c $(BUILDFILES) | $(OBJ_SUBDIRS)
					$(CC) $(CFLAGS) $(MACROS) $(INCFLAGS) -c $< -o $@ \
						&& echo -n $(MSG_PROGRESS)


#	Pre-processing and dependency file creation

$(DEP_DIR)/%.d	:	$(SRC_DIR)/%.c $(BUILDFILES) | $(DEP_SUBDIRS)
					$(CC) $(CFLAGS) $(MACROS) $(INCFLAGS) \
						-M -MP -MF $@ -MT "$(OBJ_DIR)/$*.o $@" $<


#	Mirror directory structure of source files for build artifacts

$(OBJ_SUBDIRS) \
$(DEP_SUBDIRS)	:
					mkdir -p $@


#	Cleaning

clean			:
					rm -f $(OBJ) $(DEP)
ifneq (,$(wildcard $(OBJ_DIR)))
					-find $(OBJ_DIR) -type d -empty -delete
endif
ifneq (,$(wildcard $(DEP_DIR)))
					-find $(DEP_DIR) -type d -empty -delete
endif

fclean			:	clean
					rm -f $(NAME)

ffclean			:	fclean
					rm -rf $(OBJ_DIR) $(DEP_DIR)

re				:	fclean
					$(MAKE) all


#	Include dependency files

ifeq (,$(filter clean fclean re,$(MAKECMDGOALS)))
    ifneq (,$(wildcard $(OBJ_DIR)))
        -include	$(DEP)
    endif
endif


# **************************** COLORS ******************************* #

STY_RES			:=	"\e[0m"
STY_BOL			:=	"\e[1m"
STY_ITA			:=	"\e[3m"
STY_UND			:=	"\e[4m"
STY_RED			:=	"\e[31m"
STY_GRE			:=	"\e[32m"
STY_YEL			:=	"\e[33m"
STY_BLU			:=	"\e[34m"
STY_MAG			:=	"\e[35m"
STY_CYA			:=	"\e[36m"
STY_WHI			:=	"\e[37m"
STY_GRA			:=	"\e[90m"
STY_WHI_BRI		:=	"\e[97m"
STY_BLA_BG		:=	"\e[40m"
STY_RED_BG		:=	"\e[41m"
STY_GRE_BG		:=	"\e[42m"
STY_YEL_BG		:=	"\e[43m"
STY_BLU_BG		:=	"\e[44m"
STY_MAG_BG		:=	"\e[45m"
STY_CYA_BG		:=	"\e[46m"
STY_WHI_BG		:=	"\e[47m"
STY_GRA_BG		:=	"\e[100m"
STY_WHI_BRI_BG	:=	"\e[107m"


# **************************** CUSTOM MESSAGES ******************************* #

################################################################################
MSG_INFO		:=	$(STY_ITA)$(STY_WHI)" Make version: $(MAKE_VERSION)\n\
					Compiler version: $(CC_VERSION)\n"$(STY_RES)
################################################################################
MSG_START		:=	$(STY_ITA)"Building $(NAME) ... "$(STY_RES)
################################################################################
MSG_PROGRESS	:=	"🍽️ "
################################################################################
MSG_SUCCESS		:=	$(STY_BOL)$(STY_ITA)$(STY_WHI_BRI)"\nDONE!"$(STY_RES)
################################################################################
MSG_NO_CHNG		:=	$(STY_ITA)$(STY_WHI)"Everything up-to-date!"$(STY_RES)
################################################################################
MSG_FAILURE		:=	$(STY_BOL)$(STY_ITA)$(STY_RED)"BUILD FAILED!"$(STY_RES)
################################################################################
MSG_VERBOSE		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_YEL)"-------------- VERBOSE MODE --------------\n"$(STY_RES)
ifneq (,$(filter verbose%,$(MAKECMDGOALS)))
MSG_MODE		:=	$(MSG_VERBOSE)
endif
################################################################################
MSG_COLUMN1		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_GRE)"--------- PRINTOUTS IN 1 COLUMN ----------\n"$(STY_RES)
MSG_COLUMN2		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_BLU)"--------- PRINTOUTS IN 2 COLUMNS ---------\n"$(STY_RES)
MSG_COLUMN3		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_MAG)"--------- PRINTOUTS IN 3 COLUMNS ---------\n"$(STY_RES)
ifneq (,$(filter verbose1 column1,$(MAKECMDGOALS)))
MSG_COLUMN		:=	$(MSG_COLUMN1)
else ifneq (,$(filter verbose2 column2,$(MAKECMDGOALS)))
MSG_COLUMN		:=	$(MSG_COLUMN2)
else ifneq (,$(filter verbose3 column3,$(MAKECMDGOALS)))
MSG_COLUMN		:=	$(MSG_COLUMN3)
endif
################################################################################
MSG_NO_COLOR	:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_WHI_BRI)"------------- NO COLOR MODE --------------\n"$(STY_RES)
ifneq (,$(filter nocolor,$(MAKECMDGOALS)))
MSG_MODE		:=	$(MSG_NO_COLOR)
endif
################################################################################


# *************************** MAKEFILE DEBUGGING ***************************** #

#	Execute "make print-[variable name]" to list the variable's values

print-%			:
					echo $* = $($*)


# ********************************* NOTES ************************************ #
