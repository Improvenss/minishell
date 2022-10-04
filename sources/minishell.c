/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:45:01 by gsever            #+#    #+#             */
/*   Updated: 2022/10/04 16:20:05 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Set the argument object
 * 		Standart env değerini struct yapısına atıyoruz.
 * 		! "extern char" env yapısını bildirmeye yarıyor.
 * 
 * @param base 
 * @fn ft_split()
 * @fn env_findret()
 * @fn print_error()
 * @fn strerror()
 * @return int -> for error code.
 */
int	set_argument(t_base *base)
{
	extern char	**environ;
	int			i;

	base->environ = environ;
	base->env = NULL;
	i = -1;
	while (base->environ[++i])
		env_struct(base, base->environ[i]);
	base->PATH = ft_split(env_findret(base, "PATH"), ':');
	if (base->PATH == NULL)
		return (print_error(T_NAME, NULL, NULL, strerror(ENOMEM)));
	return (0);
}
/**
 * @brief Starting here.
 * 
 * @fn signal(SIGINT, action) -> CTRL+C
 * @fn signal(SIGQUIT, SIG_IGN) -> CTRL+\
 * NOTE: CTRL+D -> readline = NULL oluyor, NULL kontrolunu yaparak exit();
 * NOTE: 
 * @fn 
 * @note CTRL+C yapildiginda ^C yaziyor onu yazdirmamamiz lazim.
 */
void	minishell(void)
{
	t_base	base;

	if (set_argument(&base) == ERROR)
		exit(EXIT_FAILURE);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, action);
		if (isatty(STDIN_FILENO))
			base.input_line = readline(T_NAME);
		if (base.input_line == NULL)
		{
			ft_putendl_fd(RED"exit"END, STDERR_FILENO);
			rl_clear_history();
			exit(0);
		}
		if (history_empty_check(base.input_line))
			add_history(base.input_line);
		if (syntax(&base))
			command_run(&base);
	}
}
