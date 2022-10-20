/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:47:06 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/13 08:47:06 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 * @param base 
 * @note 
 * 	TODO: exit argv1
 * 	TODO: DEBUG=tirnaksiz hali dahil edilecek "tirnakli hali calisiyor"
 */
void	minishell(t_base *base)
{
	signal(SIGQUIT, SIG_IGN);
	commands_init(base);
	while (1)
	{
		signal(SIGINT, action);
		base->input_line = readline(T_NAME);
		if (!base->input_line)
			break;
		if (history_empty_check(base->input_line))
			add_history(base->input_line);
		lexer(base, base->input_line);
		if (lexer_syntax(base->lexer) == ERROR)
			exit_status(1, 0);
		else
			cmd(base);
		lexer_free(&base->lexer);
		cmd_free(&base->cmd);
		free(base->input_line);
	}
	all_free(&base);
	exit(0);
}