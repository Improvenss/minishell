/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:45:01 by gsever            #+#    #+#             */
/*   Updated: 2022/09/30 14:00:27 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Set the argument object
 * 		Standart env değerini struct yapısına atıyoruz.
 * 		! "extern char" env yapısını bildirmeye yarıyor.
 * 
 * @param base 
 */
void	set_argument(t_base *base)
{
	extern char	**environ;

	base->environ = environ;
	base->PATH = ft_split(env_findret("PATH=", base), ':');
}

/**
 * @brief Starting here.
 * 
 * @fn signal(SIGINT, action) -> CTRL+C
 * @fn signal(SIGQUIT, SIG_IGN) -> CTRL+\
 * NOTE: CTRL+D -> readline = NULL oluyor, NULL kontrolunu yaparak exit();
 * NOTE: 
 * @fn 
 * @not CTRL+C yapildiginda ^C yaziyor onu yazdirmamamiz lazim.
 */
void	minishell(void)
{
	t_base	base;

	set_argument(&base);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, action);
		if (isatty(STDIN_FILENO))
			base.input_line = readline(T_NAME);
		if (base.input_line == NULL)
		{
			printf(RED"exit\n"END);
			rl_clear_history();
			exit(0);
		}
		if (history_empty_check(base.input_line))
			add_history(base.input_line);
		if (syntax(&base))
			command_run(&base);
	}
}
