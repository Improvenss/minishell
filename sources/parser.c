/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:17:24 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/06 22:17:24 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser_cmd_create(t_base *base, int type)
{
	t_parser	*new;
	t_parser	*tmp;
	
	new = (t_parser *)malloc(sizeof(t_parser));
	if (!new)
		return (print_error(T_NAME, NULL, NULL, strerror(ENOMEM)));
	new->type = type;
	//printf("type %d\n", type);
	new->argv = NULL;
	new->redir = NULL;
	new->next = NULL;
	tmp = base->parser;
	while (tmp != NULL)
		tmp = tmp->next;
	tmp = new;
	if (base->parser == NULL)
	{
		base->parser = new;
		base->parser->next = NULL;
	}
	else
	{
		tmp = base->parser;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

int	parser_cmd_type(t_lexer *lexer)
{
	if (lexer == NULL)
		return (ERROR);
	else if (lexer->flag & (TOK_TEXT | TOK_REDIR))
		return (CMD_SCMD);
	else if (lexer->flag & TOK_BIN_OP)
	{
		if (lexer->str[0] == '&')
			return (CMD_AND);
		else if (lexer->str[0] == '|')
			return (CMD_OR);
	}
	else if (lexer->str[0] & TOK_PIPE)
		return (CMD_PIPE);
	else if (lexer->str[0] & TOK_O_BRACKET)
		return (CMD_O_BRACKET);
	else if (lexer->str[0] & TOK_C_BRACKET)
		return (CMD_C_BRACKET);
	return (ERROR);
}

int	parser_cmd(t_base *base)
{
	t_lexer *tmp;

	tmp = base->lexer;
	while (tmp)
	{
		if (parser_cmd_create(base, parser_cmd_type(tmp)) == ERROR)
			return (ERROR);
		//printf("--%s\n", tmp->str);
		tmp = tmp->next;
	}
	return (1);
}

int	parser(t_base *base)
{
	if (parser_cmd(base) <= 0)
		return (0);
	return (0);
}
