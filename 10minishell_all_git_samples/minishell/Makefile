NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
FILES	= minishell.c built-in/*.c command_process/*.c function_process/*.c pipe/*.c redirect/*.c
LIBFT	= libft/libft.a

A	:= /goinfre/$(USER)/brew/Cellar/readline/8.1.2/include
B	:= /goinfre/$(USER)/brew/Cellar/readline/8.1.2/lib

all : run

run : makediff
	@$(CC) -o $(NAME) $(FILES) -I$(A) -L$(B) $(CFLAGS) $(LIBFT) -lreadline

makediff :
	@make bonus -C libft

clear :
	@rm -rf $(NAME)

fclean : clear
	@make fclean -C libft

re : fclean all

.PHONY : all run makediff clear fclean re
