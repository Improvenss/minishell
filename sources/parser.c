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

int	parser_scmd_set(t_parser *new, t_lexer **lexer)
{
	t_lexer	*next;

	while (parser_cmd_type(*lexer) == CMD_SCMD)
	{
		next = (*lexer)->next;
		printf("lexer->flag : %d\n", (*lexer)->flag);
		if ((*lexer)->flag & TOK_REDIR)
		{
			printf("%d\n", __LINE__);
			if (redir_type((*lexer)->str) == REDIR_HEREDOC)
			{
				if (parser_heredoc(*lexer) == ERROR)
					return (ERROR);
			}
			redir_lstadd(&new->redir, *lexer);
		}
		else if ((*lexer)->flag & TOK_REDIR_FILE)
			redir_lstadd(&new->redir, *lexer);
		else
			argv_lstadd(&new->argv, *lexer);
		(*lexer)->next = NULL;
		*lexer = next;
	}
	return (0);
}

t_parser	*parser_cmd_create(t_base *base, int type)
{
	t_parser	*new;
	t_parser	*tmp;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (!new)
		return (NULL);
	new->type = type;
	new->argv = NULL;
	new->redir = NULL;
	new->next = NULL;
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
	return (new);
}

/** OK:
 * @brief Lexer'deki tokenlerden cmd tipini donduruyor.
 * 
 * NOTE: Text ya da redir(< >) tipindeyse scmd donuyor.
 * 
 * @param lexer 
 * @return int 
 */
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
	t_lexer		*tmp;
	t_parser	*new;

	tmp = base->lexer;
	while (tmp)
	{
		printf("%s\n", tmp->str);
		printf("%s\n", tmp->next->str);
		printf("%d\n", __LINE__);
		new = parser_cmd_create(base, parser_cmd_type(tmp));
		printf("%d\n", __LINE__);
		if (new == NULL || (new->type == CMD_SCMD && parser_scmd_set(new, &tmp) == ERROR))
		{
			printf("yandik\n");
			return (ERROR);
		}
		printf("%d\n", __LINE__);
		printf("%s\n", tmp->str);
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
