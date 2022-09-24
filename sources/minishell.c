/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:45:01 by gsever            #+#    #+#             */
/*   Updated: 2022/09/24 10:32:58 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
