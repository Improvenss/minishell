# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/15 17:54:15 by gsever            #+#    #+#              #
#    Updated: 2022/09/26 08:50:30 by akaraca          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

#	Flags for compile
CC			= gcc
FLAGS		= -Wall -Werror -Wextra

#	All process use for compiling.
UNAME		:= $(shell uname -s)
NUMPROC		:= 8

OS			= NULL

#	Libft Part --> OK
LIBFTDIR		= ./libraries/libft
# READLINE_DIR	= ../includes/readline/lib
# LIBFT		= $(LIBFTDIR)/libft.a

# gcc minishell.c -L../includes/readline/lib -I../includes/readline/include -lreadline && ./a.out

#	READLINE_H
READLINE_INC_MACOS	:= /goinfre/$(USER)/brew/include
READLINE_LIB_MACOS	:= /goinfre/$(USER)/brew/lib

#	Locations Part --> OK
LIBRARIES	= \
	-L$(LIBFTDIR)/ -lft \
	-L$(READLINE_LIB_MACOS) -lreadline
#	-L/goinfre/homebrew/opt/readline/lib -lreadline -fcommon
#	-L/opt/homebrew/Cellar/readline/8.1.2/lib -lreadline

# -L.brew/opt/readline/lib -lreadline
INCLUDES	= \
	-I$(HEADERS_DIRECTORY) \
	-I$(LIBFTDIR)/includes \
	-I$(READLINE_INC_MACOS)
#	-I/goinfre/homebrew/opt/readline/include -fcommon
#	-I/opt/homebrew/Cellar/readline/8.1.2/include/
# -I$(READLINE_DIR)/include

#	HEADERS Parts --> Kutuphane --> OK
HEADERS_DIRECTORY = ./includes/
# HEADERS_LIST = $(subst $(HEADERS_DIRECTORY),,$(wildcard $(HEADERS_DIRECTORY)*.h))
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

#	Source Files --> OK
SOURCES_DIRECTORY = ./sources/
SOURCES_LIST = $(subst $(SOURCES_DIRECTORY),,$(wildcard $(SOURCES_DIRECTORY)*.c))
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

#	Object Files --> (Compiled files directory) -> OK
OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

#	COLORS --> 🟥 🟩 🟦
LB		= \033[0;36m
BLUE	= \033[0;34m
YELLOW	= \033[0;33m
GREEN	= \033[0;32m
RED		= \033[0;31m
RESET	= \033[0m
X		= \033[m

#	LEAKS --> Checking this program have memory leaks.
LEAKS_PH	= leaks -atExit -- ./minishell
#	You can use //system("leaks a.out");

#	Compiling with all threads.
ifeq ($(UNAME), Linux)
	NUMPROC	:= $(shell grep -c ^processor /proc/cpuinfo)
#	OS = "$(UNAME)tan baglaniyorsun bruh"
else ifeq ($(UNAME), Darwin)
	NUMPROC	:= $(shell sysctl -n hw.ncpu)
	OS = "Macos'tan baglaniyorsun bruh"
endif
# You can use --> man sysctl -> shell: sysctl -a | grep "hw.ncpu"

.PHONY: all clean fclean re leaksps

all:
	@$(MAKE) $(NAME) -j $(NUMPROC) --no-print-directory
#	@$(MAKE) -s $(NAME) -j $(NUMPROC)

#	Compiling
$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	@printf "%-57b %b" "$(BLUE)COMPILED $(LB)$@" "$(GREEN)[✓]$(X)\n"

$(NAME): libft $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) $(LIBRARIES) -o $(NAME)
	@printf "%-57b %b" "$(GREEN)CREATED $(NAME)" "[FINISHED]$(X)\n"
	@echo $(OS) $(NUMPROC) "cekirdekle derlendi"

#	Objects file creating
$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

#	My Library --> OK
libft:
ifneq ($(MAKECMDGOALS), $(filter $(MAKECMDGOALS), $(NAME)))
	@make -C $(LIBFTDIR) $(MAKECMDGOALS) --silent
else
	@make -C $(LIBFTDIR) --silent
endif


clean: libft
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"

fclean: libft clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

test:
	@cd testers && bash tester.sh a

leaksps:
	$(LEAKS_PH)
