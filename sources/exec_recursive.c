/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_recursive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:42:30 by gsever            #+#    #+#             */
/*   Updated: 2022/10/12 14:15:55 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	expanded_str_get(t_lexer *token, char __unused **exp_str, int *i)
{
	if (token->str[*i] == '$' && token->str[*i + 1] == '?')
	{
		// if (expanded_str_append_exit_code(exp_str) == ERROR)
		// 	return (ERROR);
		(*i)++;
	}
	return (0);
}

static int	expand_var_token(t_lexer *token)
{
	char	*exp_str;
	int		i;

	if (token->str == NULL || (token->flag & TOK_S_QUOTE)
		|| !ft_strchr(token->str, '$')
		|| (token->flag & TOK_REDIR_FILE && token->flag & TOK_D_QUOTE))
		return (0);
	exp_str = ft_strdup("");
	if (exp_str == NULL)
		return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
	i = 0;
	while (token->str[i])
	{
		while (token->str[i] == '$' && token->str[i + 1] == '$')
			i++;
		if (expanded_str_get(token, &exp_str, &i) == ERROR)
		{
			free(exp_str);
			return (ERROR);
		}
		i++;
	}
	free(token->str);
	token->str = exp_str;
	return (0);
}

int	expand_var_token_list(t_lexer *token)
{
	t_lexer	*iter;

	iter = token;
	while (iter)
	{
		if (expand_var_token(iter) == ERROR)
			return (ERROR);
		iter = iter->next;
	}
	return (0);
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
 * @fn exec_recursive()
 * @return int 
 */
int exec_recursive(t_base *base, bool subshell)
{
	printf("base->parser->type: %d\n", base->parser->type);
	if (base->parser->type == CMD_SCMD)
	{
		base->exit_status = exec_cmd(base->parser, subshell, base->parser);
		printf("exec_cmd calisti\n");
	}
	if (base->parser->next)
	{
		base->parser = base->parser->next;
		while (base->parser && exec_operator_skip(base))
			base->parser = base->parser->next->next;
		if (base->parser != NULL)
		{
			base->parser = base->parser->next;
			printf("icerideki base->parser->type: %d\n", base->parser->type);
			base->exit_status = exec_recursive(base, subshell);
		}
	}
	return (base->exit_status);
}