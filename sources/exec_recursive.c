/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_recursive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:42:30 by gsever            #+#    #+#             */
/*   Updated: 2022/10/13 16:14:47 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/** @brief Eger operatoru CMD_AND(&&) ya da CMD_OR(||) oldugu zaman
 * 
 * @param base parser ve exit_status icin.
 * @return  OK: CMD_AND(&&) ya da CMD_OR(||) -> ture \
 * @return NOK: -> false.
 */
static bool	exec_operator_skip(t_base *base)
{
	if (base->parser->type & CMD_AND && base->exit_status != 0)
		return (true);
	else if (base->parser->type & CMD_OR && base->exit_status != 0)
		return (true);
	return (false);
}

int	expand_var(t_parser *parser)
{
	int		status;

	status = expand_var_token_list(parser->argv);
	if (status != ERROR)
		status = expand_var_token_list(parser->redir);
	// if (status != ERROR)
	// 	status = expand_var_splitting(&parser->argv);
	// if (status != ERROR)
	// 	status = expand_var_splitting(&parser->redir);
	return (status);
}

int	exec_cmd_preperation(t_parser *parser, char ***argv)
{
	// t_parser	*redir_undo;
	int			status;

	status = 0;
	*argv = NULL;
	if (expand_var(parser) == ERROR)
		return (ERROR);
	return (0);
}

int	exec_cmd(t_parser *parser, bool __unused subshell, t_parser __unused *free)
{
	char	**argv;
	// int		pid;
	// int		status;

	if (exec_cmd_preperation(parser, &argv) == ERROR)
		return (ERROR);
	if (!parser->argv)
		return (0);
	return (0);
}

/**
 * @brief parser'lenmis lexer'den sonra; parser'li halini calistirmak icin.
 * 
 * @param base 
 * @param subshell 
 * @fn exec_cmd(): Pipe ya da Group olmadan sadece main process'te
 *  calistirilacaksa.
 * @fn exec_operator_skip(): && ya da || varsa 'true' donup calistirilacak.
 *  Asil amaci; 
 * @fn exec_recursive()
 * @return int 
 */
int	exec_recursive(t_base *base, bool subshell)
{
	// printf("base->parser->type: %d, %s\n", base->parser->type, base->parser->argv->str);
	if (base->parser->type == CMD_SCMD)
	{
		base->exit_status = exec_cmd(base->parser, subshell, base->parser);
	}
	if (base->parser->next)
	{
		base->parser = base->parser->next;
		while (base->parser && exec_operator_skip(base))
		{
			printf("lan nere gidion\n");
			base->parser = base->parser->next->next;
		}
		if (base->parser != NULL)
		{
			base->parser = base->parser->next;
			base->exit_status = exec_recursive(base, subshell);
		}
	}
	return (base->exit_status);
}