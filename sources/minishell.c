/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:45:01 by gsever            #+#    #+#             */
/*   Updated: 2022/09/27 14:05:22 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*env_findret(char *env_name, t_base *base)
{
	int	i;
	int	l;
	int	count;

	i = 0;
	while (base->environ[i])
	{
		l = 0;
		count = 0;
		while (base->environ[i][l])
		{
			if (base->environ[i][count] == env_name[count])
				count++;
			if (env_name[count] == '\0')
				return (&base->environ[i][count]);
			l++;
		}
		i++;
	}
	return (NULL);
}

/**
 * @brief Set the argument object
 * 		Standart env değerini struct yapısına atıyoruz.
 * 		! "extern char" env yapısını bildirmeye yarıyoruz.
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
 * @fn signal(SIGQUIT, action) -> CTRL+\
 * NOTE: CTRL+D -> readline = NULL oluyor, NULL kontrolunu yaparak exit();
 * NOTE: 
 * @fn 
 * @not CTRL+C yapildiginda ^C yaziyor onu yazdirmamamiz lazim.
 */
void	minishell(void)
{
	t_base	base;

	set_argument(&base);
	while (1)
	{
		signal(SIGINT, action);
		signal(SIGQUIT, SIG_IGN);
		if (isatty(STDIN_FILENO))
			base.input_line = readline(T_NAME);
		if (!base.input_line)
		{
			printf("exit\n");
			exit(0);
		}
		if (history_empty_check(base.input_line))
			add_history(base.input_line);
		if (syntax(&base))
			command_run(&base);
	}
}
