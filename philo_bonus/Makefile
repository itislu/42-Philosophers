# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 22:39:28 by ldulling          #+#    #+#              #
#    Updated: 2024/08/04 16:18:57 by ldulling         ###   ########.fr        #
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

CC 				?=	cc
CC_VERSION		:=	$(shell $(CC) --version | head -1)
CFLAGS_STD		:=	-Wall -Wextra -Werror
CFLAGS_DBG		:=	-ggdb3
CFLAGS_SAN		:=	-fsanitize=thread,undefined,bounds,float-divide-by-zero
CFLAGS_OPT		:=	-O3
CFLAGS 			?=	$(CFLAGS_STD) $(CFLAGS_DBG)
INCFLAGS 		:=	$(addprefix -I,$(INC_DIR))
LDLIBS			:=	-pthread
MAKEFLAGS		:=	-j -s


#	Macro definitions

COLUMN1			:=	'""'
COLUMN2			:=	'"                                   "'
COLUMN3			:=	'"                                                                      "'

export				MACROS
ifneq (,$(filter verbose%,$(MAKECMDGOALS) $(MODE)))
MACROS			:=	-D VERBOSE=1
endif
ifneq (,$(filter verbose1 column1,$(MAKECMDGOALS) $(MODE)))
MACROS			+=	-D COLUMN1='"$(COLUMN1)"' \
					-D COLUMN2='"$(COLUMN1)"' \
					-D COLUMN3='"$(COLUMN1)"'
else ifneq (,$(filter verbose2 column2,$(MAKECMDGOALS) $(MODE)))
MACROS			+=	-D COLUMN1='"$(COLUMN1)"' \
					-D COLUMN2='"$(COLUMN2)"' \
					-D COLUMN3='"$(COLUMN2)"'
else ifneq (,$(filter verbose3 column3,$(MAKECMDGOALS) $(MODE)))
MACROS			+=	-D COLUMN1='"$(COLUMN1)"' \
					-D COLUMN2='"$(COLUMN2)"' \
					-D COLUMN3='"$(COLUMN3)"'
endif
ifneq (,$(filter nocolor,$(MAKECMDGOALS) $(MODE)))
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

HELGRINDFLAGS	=	--tool=helgrind \
					--read-var-info=yes \
					--show-error-list=yes \
					--trace-children=yes

DRDFLAGS		=	--tool=drd \
					--read-var-info=yes \
					--show-error-list=yes \
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

export				CC CFLAGS MAKECMDGOALS MAKEFLAGS

PHONY_TARGETS	:=	all verbose verbose1 verbose2 verbose3 column1 column2 column3 nocolor \
					opt san run val hel drd clear clean fclean ffclean re
ENV_VARIABLES	:=	MODE ARGS
HELP_TARGETS	:=	help help-print \
					$(addprefix help-,$(PHONY_TARGETS) $(ENV_VARIABLES)) \
					$(addsuffix -help,$(PHONY_TARGETS) $(ENV_VARIABLES))
PHONY_TARGETS	+=	$(HELP_TARGETS)
export .PHONY	:	$(PHONY_TARGETS)

REBUILD_TARGETS	:=	verbose	verbose1 verbose2 verbose3 column1 column2 column3 nocolor \
					opt san re

.DEFAULT		:
					$(MAKE) help

.DEFAULT_GOAL	:=	all

MODE			?=	all


#	Compilation

help-all		:
					echo "Build the project."
					echo "This is the default target when no target is specified."

all				:
					if $(MAKE) --question $(NAME); then \
						echo -n $(MSG_NO_CHNG); \
						echo -n $(MSG_HELP); \
					else \
						echo -n $(MSG_MODE); \
						echo -n $(MSG_COLUMN); \
						echo -n " "$(MSG_INFO); \
						echo -n " "$(MSG_HELP); \
						echo -n $(MSG_START); \
						if $(MAKE) $(NAME); then \
							echo; \
							echo -n $(MSG_SUCCESS); \
						else \
							echo; \
							echo -n $(MSG_FAILURE); \
							exit 42; \
						fi; \
					fi


help-verbose help-verbose1 help-verbose2 help-verbose3:
					echo "Build the project in verbose mode."
					echo "Verbose mode prints extra information to see what each process is doing."
					echo "Optionally, printouts can be split into 1, 2, or 3 columns (default is 1)."
					echo "  Column 1: The philosophers with uneven ID."
					echo "  Column 2: The philosophers with even ID."
					echo "  Column 3 (only for uneven amount of philosophers): The philosophers which have to wait double the time to eat."

help-column1 help-column2 help-column3:
					echo "Build the project with printouts split into 1, 2, or 3 columns."
					echo "  Column 1: The philosophers with uneven ID."
					echo "  Column 2: The philosophers with even ID."
					echo "  Column 3 (only for uneven amount of philosophers): The philosophers which have to wait double the time to eat."

help-nocolor	:
					echo "Build the project without colors in printouts."
					echo "Useful for redirecting the output into a file and pasting it into the philosophers-visualizer."

help-opt		:
					echo "Build the project with the following compiler optimization flags:"
					echo "  $(CFLAGS_OPT)"

help-san		:
					echo "Rebuild the project with the following sanitizers enabled:"
					echo "  $(CFLAGS_SAN)"

opt				:	CFLAGS := $(CFLAGS_STD) $(CFLAGS_OPT)
san				:	CFLAGS := $(CFLAGS_STD) $(CFLAGS_DBG) $(CFLAGS_SAN)
verbose	verbose1 verbose2 verbose3 column1 column2 column3 nocolor opt san: re
					$(MAKE) clean
					if [ "$(MAKECMDGOALS)" = "$@" ] && [ -n "$(ARGS)" ]; then \
						"./$(NAME)" $(ARGS); \
					fi


help-run		:
					echo "Build the project and run the executable."
					echo "Arguments to the program can be passed via the ARGS variable."
					echo "Usage: make run ARGS=\"<arg1> <arg2> <...>\""

run				:	$(MODE)
					"./$(NAME)" $(ARGS)


help-val		:
					echo "Build the project and run the executable with valgrind."
					echo "The following valgrind flags are used:"
					echo "$(VALGRINDFLAGS)" | tr ' ' '\n' | sed 's/^/  /'
					echo "Arguments to the program can be passed via the ARGS variable."
					echo "Usage: make val ARGS=\"<arg1> <arg2> <...>\""

val				:	$(MODE)
					$(VALGRIND) $(VALGRINDFLAGS) "./$(NAME)" $(ARGS)


help-hel		:
					echo "Build the project and run the executable with helgrind."
					echo "The following helgrind flags are used:"
					echo "$(HELGRINDFLAGS)" | tr ' ' '\n' | sed 's/^/  /'
					echo "Arguments to the program can be passed via the ARGS variable."
					echo "Usage: make hel ARGS=\"<arg1> <arg2> <...>\""
					echo
					echo "Disclaimer:"
					echo "Helgrind will report \"sem_wait succeeded on semaphore without prior sem_post\" errors."
					echo "This seems to be an issue with helgrind."
					echo "When a semaphore gets increased by one process, and another process waits for that semaphore, helgrind does not see that and reports this error."
					echo "You can see this happening by running DRD and adding '--trace-semaphore=yes' to the DRD flags."
					echo "You will notice that even though one process increased the semaphore, for the other process it still shows as 0."

hel				:	$(MODE)
					$(VALGRIND) $(HELGRINDFLAGS) "./$(NAME)" $(ARGS)


help-drd		:
					echo "Build the project and run the executable with DRD."
					echo "The following DRD flags are used:"
					echo "$(DRDFLAGS)" | tr ' ' '\n' | sed 's/^/  /'
					echo "Arguments to the program can be passed via the ARGS variable."
					echo "Usage: make drd ARGS=\"<arg1> <arg2> <...>\""
					echo
					echo "Disclaimer:"
					echo "DRD will report \"Invalid semaphore\" errors."
					echo "This seems to be an issue with DRD."
					echo "When a semaphore gets increased by one process, and another process waits for that semaphore, DRD does not see that and reports this error."
					echo "You can see this by adding '--trace-semaphore=yes' to the DRD flags."
					echo "You will notice that even though one process increased the semaphore, for the other process it still shows as 0."

drd				:	$(MODE)
					$(VALGRIND) $(DRDFLAGS) "./$(NAME)" $(ARGS)


help-clear		:
					echo "Clear the terminal and build the project."

clear			:
					clear
					$(MAKE) $(MODE)
					if [ "$(MAKECMDGOALS)" = "$@" ] && [ -n "$(ARGS)" ]; then \
						"./$(NAME)" $(ARGS); \
					fi


help			:
					echo "Usage: make [target [MODE=<mode>] [ARGS=\"<arg1> <arg2> <...>\"]]"
					echo
					echo "Targets:"
					echo "  all              Build the project (default target)"
					echo "  verbose[1|2|3]   Build the project in verbose mode with printouts in 1, 2, or 3 columns (default: 1)"
					echo "  column<1|2|3>    Build the project with printouts in 1, 2, or 3 columns"
					echo "  nocolor          Build the project without colors in printouts"
					echo "  opt              Build the project with optimizations"
					echo "  san              Build the project with sanitizers"
					echo "  run              Build and run the project"
					echo "  val              Build and run the project with valgrind"
					echo "  hel              Build and run the project with helgrind"
					echo "  drd              Build and run the project with DRD"
					echo "  clear            Clear the terminal and build the project"
					echo "  clean            Remove build artifacts"
					echo "  fclean           Remove build artifacts and executable"
					echo "  ffclean          Remove build artifacts and executable without checking for unknown files"
					echo "  re               Rebuild the project"
					echo "  print-%          Print the value of a Makefile variable (replace % with variable name)"
					echo "  help             Display this message"
					echo "  help-% | %-help  Display more information for a specific target (replace % with target name)"
					echo
					echo "Environment Variables:"
					echo "  MODE             Build mode to combine with other targets"
					echo "  ARGS             If specified, the program will run with those arguments after compilation."

help-help		:
					echo "Display more information for a specific target by appending or prepending help."
					echo "Usage: make help-<target> | make <target>-help"

help-MODE MODE-help:
					echo "Build mode to combine with other targets."
					echo "Usage: make <target> MODE=<mode>"

help-ARGS ARGS-help:
					echo "If specified, the program will run with those arguments after compilation."
					echo "Usage: make <target> ARGS=\"<arg1> <arg2> <...>\""

%-help:
					$(MAKE) help-$(subst -help,,$@)


#	Executable linking

$(NAME)			:	$(LIBRARIES) $(OBJ)
					$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)


#	Source file compiling

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c $(BUILDFILES) | $(OBJ_SUBDIRS)
					$(CC) $(CFLAGS) $(MACROS) $(INCFLAGS) -c $< -o $@ \
						&& echo -n $(MSG_PROGRESS)


#	Pre-processing and dependency file creation

$(DEP_DIR)/%.d	:	$(SRC_DIR)/%.c $(BUILDFILES) | $(DEP_SUBDIRS)
					$(CC) $(CFLAGS) $(MACROS) $(INCFLAGS) -M -MP -MF $@ -MT "$(OBJ_DIR)/$*.o $@" $<


#	Mirror directory structure of source files for build artifacts

$(OBJ_SUBDIRS) \
$(DEP_SUBDIRS)	:
					mkdir -p $@


#	Cleaning

help-clean		:
					echo "Remove build artifacts."

clean			:
					echo -n $(MSG_CLEAN)
					rm -f $(OBJ) $(DEP)
                    ifneq (,$(wildcard $(OBJ_DIR)))
						-find $(OBJ_DIR) -type d -empty -delete
                    endif
                    ifneq (,$(wildcard $(DEP_DIR)))
						-find $(DEP_DIR) -type d -empty -delete
                    endif
					echo -n $(MSG_SUCCESS)


help-fclean		:
					echo "Remove build artifacts and the executable."

fclean			:
					echo -n $(MSG_FCLEAN)
					$(MAKE) clean
					rm -f $(NAME)
					echo -n $(MSG_SUCCESS)


help-ffclean	:
					echo "Remove build artifacts and the executable without checking for unknown files."

ffclean			:
					echo -n $(MSG_FFCLEAN)
					$(MAKE) fclean
					rm -rf $(OBJ_DIR) $(DEP_DIR)
					echo -n $(MSG_SUCCESS)


help-re			:
					echo "Rebuild the project."

re				:
					$(MAKE) fclean
					MAKELEVEL=$$(( $(MAKELEVEL) - 1 )) $(MAKE) all


#	Include dependency files

ifeq (,$(filter $(HELP_TARGETS) $(REBUILD_TARGETS) clean fclean ffclean,$(MAKECMDGOALS)))
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
MSG_PROGRESS	:=	"🍽️ "
################################################################################

ifeq ($(MAKELEVEL),0)
################################################################################
MSG_INFO		:=	$(STY_ITA)$(STY_WHI)"Make version: $(MAKE_VERSION)\n\
					Compiler version: $(CC_VERSION)"$(STY_RES)"\n"
################################################################################
MSG_HELP		:=	$(STY_ITA)$(STY_WHI)"Run 'make help' to see all available Makefile targets."$(STY_RES)"\n"
################################################################################
ifneq (,$(filter $(REBUILD_TARGETS),$(MAKECMDGOALS) $(MODE)))
MSG_START		:=	$(STY_ITA)"Rebuilding $(NAME) ... "$(STY_RES)
else
MSG_START		:=	$(STY_ITA)"Building $(NAME) ... "$(STY_RES)
endif
################################################################################
MSG_SUCCESS		:=	$(STY_BOL)$(STY_ITA)$(STY_WHI_BRI)"DONE!"$(STY_RES)"\n"
################################################################################
MSG_NO_CHNG		:=	$(STY_ITA)$(STY_WHI)"Everything up-to-date!"$(STY_RES)"\n"
################################################################################
MSG_FAILURE		:=	$(STY_BOL)$(STY_ITA)$(STY_RED)"BUILD FAILED!"$(STY_RES)"\n"
################################################################################
MSG_VERBOSE		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_YEL)"-------------- VERBOSE MODE --------------"$(STY_RES)"\n"
ifneq (,$(filter verbose%,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_VERBOSE)
endif
################################################################################
MSG_NO_COLOR	:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_WHI_BRI)"------------- NO COLOR MODE --------------"$(STY_RES)"\n"
ifneq (,$(filter nocolor,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_NO_COLOR)
endif
################################################################################
MSG_OPT			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_GRE)"----------- OPTIMIZATION MODE ------------"$(STY_RES)"\n"
ifneq (,$(filter opt,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_OPT)
endif
################################################################################
MSG_SAN			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_RED)"------------- SANITIZER MODE -------------"$(STY_RES)"\n"
ifneq (,$(filter san,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_SAN)
endif
################################################################################
MSG_VAL			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_CYA)"------------ VALGRIND MODE ---------------"$(STY_RES)"\n"
ifneq (,$(filter val,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_VAL)
endif
################################################################################
MSG_HEL			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_MAG)"------------ HELGRIND MODE ---------------"$(STY_RES)"\n"
ifneq (,$(filter hel,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_HEL)
endif
################################################################################
MSG_DRD			:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_BLU)"---------------- DRD MODE ----------------"$(STY_RES)"\n"
ifneq (,$(filter drd,$(MAKECMDGOALS) $(MODE)))
MSG_MODE		:=	$(MSG_MODE)$(MSG_DRD)
endif
################################################################################
MSG_COLUMN1		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_GRE)"--------- PRINTOUTS IN 1 COLUMN ----------"$(STY_RES)"\n"
MSG_COLUMN2		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_BLU)"--------- PRINTOUTS IN 2 COLUMNS ---------"$(STY_RES)"\n"
MSG_COLUMN3		:=	$(STY_BOL)$(STY_ITA)$(STY_UND)$(STY_MAG)"--------- PRINTOUTS IN 3 COLUMNS ---------"$(STY_RES)"\n"
ifneq (,$(filter verbose1 column1,$(MAKECMDGOALS) $(MODE)))
MSG_COLUMN		:=	$(MSG_COLUMN1)
else ifneq (,$(filter verbose2 column2,$(MAKECMDGOALS) $(MODE)))
MSG_COLUMN		:=	$(MSG_COLUMN2)
else ifneq (,$(filter verbose3 column3,$(MAKECMDGOALS) $(MODE)))
MSG_COLUMN		:=	$(MSG_COLUMN3)
endif
################################################################################
MSG_CLEAN		:=	$(STY_ITA)"Cleaning up build artifacts ... "$(STY_RES)"\n"
################################################################################
MSG_FCLEAN		:=	$(STY_ITA)"Cleaning up build artifacts and executable ... "$(STY_RES)"\n"
################################################################################
MSG_FFCLEAN		:=	$(STY_ITA)"Forcefully cleaning up build artifacts and executable ... "$(STY_RES)"\n"
################################################################################
endif


# *************************** MAKEFILE DEBUGGING ***************************** #

help-print		:
					echo "Print the value of a Makefile variable by appending the variable name to print-."
					echo "Useful for Makefile debugging."
					echo "Usage: make print-<variable name>"

print-%			:
					echo $* = $($*)


# ********************************* NOTES ************************************ #
