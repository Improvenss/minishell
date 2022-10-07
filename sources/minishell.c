/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:27:26 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/07 14:41:45 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_mark_files(t_lexer *lexer)
{
	while (lexer)
	{
		if (lexer->flag == TOK_REDIR)
		{
			if (lexer->next == NULL || lexer->next->flag != TOK_TEXT)
				return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_REDIR)); // aa >'\0' veya a >>>'\0' veya a <<< b'\0'
			lexer = lexer->next;
			lexer->flag = lexer->flag + TOK_REDIR_FILE;
			while (lexer->flag == TOK_CONNECTED)
			{
				printf("-->%d\n", lexer->flag);
				lexer->flag = lexer->flag + TOK_REDIR_FILE;
				lexer = lexer->next;
			}
		}
		lexer = lexer->next;
	}
	return (0);
}

void	prosesses(t_base *base)
{
	base->lexer = NULL;
	base->parser = NULL;
	base->exit_status = 0;
	lexer_list(base, base->input_line);
	if (lexer_syntax(base->lexer) == ERROR
	|| redir_mark_files(base->lexer) == ERROR)
		base->exit_status = ERR_SYNTAX_EXIT;
	if (base->lexer != NULL && base->exit_status != ERR_SYNTAX_EXIT)
		parser(base);
		
}

void	minishell(t_base *base)
{
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, action);
		base->input_line = readline(T_NAME);
		if (!base->input_line)
		{
			ft_putendl_fd(RED"exit"END, STDERR_FILENO);
			rl_clear_history();
			exit(0);
		}
		if (history_empty_check(base->input_line))
			add_history(base->input_line);
		prosesses(base);
	}
	rl_clear_history();
	//ft_free(base);
	//exit(base->exit_status);
}
