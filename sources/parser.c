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














int	cmd_type(t_lexer *lexer)
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
	else if (lexer->flag & TOK_PIPE)
		return (CMD_PIPE);
	else if (lexer->flag & TOK_O_BRACKET)
		return (CMD_O_BRACKET);
	else if (lexer->flag & TOK_C_BRACKET)
		return (CMD_C_BRACKET);
	return (ERROR);
}

t_parser *cmd_crate(int type)
{
	t_parser *new;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->argv = NULL;
	new->redir = NULL;
	new->element = NULL;
	new->next = NULL;
	return (new);
}

void	parser_lstadd(t_parser **parser, t_parser *new)
{
	t_parser *tmp;

	tmp = *parser;
	if (*parser != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*parser = new;
}

void	lexer_lstadd(t_lexer **lst, t_lexer *new)
{
	t_lexer *tmp;

	tmp = *lst;
	if (*lst)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*lst = new;
}

int	cmd_set(t_parser *new, t_lexer **lexer)
{
	t_lexer *next;

	while (cmd_type(*lexer) == CMD_SCMD)
	{
		next = (*lexer)->next;
		if ((*lexer)->flag & TOK_REDIR)
		{
			if (redir_type((*lexer)->str) == REDIR_HEREDOC)
			{
				if (parser_heredoc(*lexer) == ERROR)
					return (ERROR);
			}
			lexer_lstadd(&new->redir, *lexer);
		}
		else if ((*lexer)->flag & TOK_REDIR_FILE)
			lexer_lstadd(&new->redir, *lexer);
		else
			lexer_lstadd(&new->argv, *lexer);
		(*lexer)->next = NULL;
		*lexer = next;
	}
	return (0);
}

t_parser	*parser_cmd(t_lexer *lexer)
{
	t_parser	*parser;
	t_parser	*new;
	//t_lexer		*next;
	
	parser = NULL;
	while (lexer != NULL)
	{
		new = cmd_crate(cmd_type(lexer));
		if (new == NULL || (new->type == CMD_SCMD 
		&& cmd_set(new, &lexer) == ERROR))
		{
			return (NULL);
		}
		if (new->type != CMD_SCMD)
		{
			lexer = lexer->next;
			// next = lexer->next;
			// lexer = next;
		}
		parser_lstadd(&parser, new);
	}
	return (parser);
}

static t_parser	*group_open(t_parser *parser)
{
	t_parser	*open;
	t_parser	*iter;

	open = NULL;
	iter = parser;
	while (iter != NULL)
	{
		if (iter->type == CMD_O_BRACKET)
			open = iter;
		else if (open && iter->type == CMD_PIPE)
			open = NULL;
		else if (open && iter->type == CMD_C_BRACKET)
			return (open);
		iter = iter->next;
	}
	return (NULL);
}

static t_parser	*group_close(t_parser *open)
{
	t_parser	*close;
	
	close = open;
	while (close && close->type != CMD_C_BRACKET)
		close = close->next;
	if (close == open)
		return (NULL);
	return (close);
}

void	lexer_lstdelone(t_lexer *node)
{
	if (node != NULL)
	{
		free(node->str);
	}
}

void	parser_lstdelone(t_parser *node)
{
	if (node != NULL)
	{
		if (node->argv != NULL)
			lexer_lstdelone(node->argv);
		if (node->redir != NULL)
			lexer_lstdelone(node->redir);
		free(node);
	}
}

int	lst_node_remove(t_parser **parser, t_parser *node)
{
	t_parser	*tmp;

	if (!parser || !(*parser) || !node)
		return (ERROR);
	if (node == *parser)
		*parser = node->next;
	else
	{
		tmp = *parser;
		while (tmp->next && tmp->next != node)
			tmp = tmp->next;
		if (tmp->next != node)
			return (ERROR);
		tmp->next = node->next;
	}
	parser_lstdelone(node);
	return (0);
}

t_parser	*lst_node_prev(t_parser *parser, t_parser *node)
{
	if (parser == node)
		return (node);
	while (parser->next && parser->next != node)
		parser = parser->next;
	if (parser->next != node)
		return (NULL);
	return (parser);
}

int	lst_relink(t_parser **parser, t_parser *node, t_parser *start, t_parser *end)
{
	t_parser	*prev;

	prev = lst_node_prev(*parser, start);
	if (prev == NULL)
		return (ERROR);
	if (start == *parser)
		*parser = node;
	else
		prev->next = node;
	if (end == NULL)
		node->next = NULL;
	else
		node->next = end->next;
	return (0);
}

int	parser_cmd_group_merge(t_parser **parser)
{
	t_parser	*group;
	t_parser	*open;
	t_parser	*close;

	open = group_open(*parser);
	close = group_close(open);
	if (!open || !close)
		return (0);
	if (open->next->type == CMD_GROUP && open->next->next == close)
	{
		lst_node_remove(parser, open);
		lst_node_remove(parser, close);
	}
	else
	{
		group = cmd_crate(CMD_GROUP);
		if (group == NULL)
			return (ERROR);
		group->element = open->next;
		lst_node_prev(*parser, close)->next = NULL;
		lst_relink(parser, group, open, close);
		parser_lstdelone(open);
		parser_lstdelone(close);
	}
	return (1);
}

static t_parser	*pipeline_start(t_parser *parser)
{
	t_parser	*iter;

	iter = parser;
	while (iter)
	{
		if ((iter->type & (CMD_SCMD | CMD_PIPELINE | CMD_GROUP))
		&& iter->next && iter->next->type == CMD_PIPE
		&& iter->next->next
		&& (iter->next->next->type & (CMD_SCMD | CMD_GROUP | CMD_PIPELINE)))
		{
			return (iter);
		}
		iter = iter->next;
	}
	return (NULL);
}

t_parser	*pipeline_end(t_parser *start)
{
	t_parser	*iter;

	iter = start;
	while (iter)
	{
		if ((iter->type & (CMD_SCMD | CMD_PIPELINE | CMD_GROUP))
		&& iter->next && iter->next->type == CMD_PIPE
		&& iter->next->next
		&& (iter->next->next->type & (CMD_SCMD | CMD_PIPELINE | CMD_GROUP)))
		{
			iter = iter->next->next;
		}
		else
			return (iter);
	}
	return (NULL);
}

static void	pipeline_cleanup(t_parser *pipeline, t_parser *start, t_parser *end)
{
	t_parser	*next;
	t_parser	*iter;

	iter = start;
	while (iter != end->next)
	{
		next = iter->next;
		if (iter->type == CMD_PIPE)
			parser_lstdelone(iter);
		else if (iter->type == CMD_PIPELINE)
		{
			parser_lstadd(&pipeline->element, iter->element);
			iter->element = NULL;
			parser_lstdelone(iter);
		}
		else
		{
			parser_lstadd(&pipeline->element, iter);
			if (iter != end)
				iter->next = NULL;
		}
		iter = next;
	}
	end->next = NULL;
}

int	parser_cmd_pipeline_merge(t_parser **parser)
{
	t_parser	*pipeline;
	t_parser	*start;
	t_parser	*end;

	start = pipeline_start(*parser);
	end = pipeline_end(start);
	if (!start || !end)
		return (0);
	pipeline = cmd_crate(CMD_PIPELINE);
	if (pipeline == NULL)
		return (ERROR);
	lst_relink(parser, pipeline, start, end);
	pipeline_cleanup(pipeline, start, end);
	return (1);
}

static int	parser_recursive_merge(t_parser **parser)
{
	int	group;
	int	pipeline;

	group = 1;
	pipeline = 1;
	while (group > 0 ||pipeline > 0)
	{
		group = parser_cmd_group_merge(parser);
		if (group == ERROR)
			return (ERROR);
		pipeline = parser_cmd_pipeline_merge(parser);
		if (pipeline == ERROR)
			return (ERROR);
	}
	return (0);
}

/**
 * @brief Lexer'leme isleminden sonra parserleme islemlerini yapiyor.
 * 
 * @param base 
 * @fn parser_cmd(): Lexer'lenmis struct'tan command'lerimizi aliyoruz.
 * @fn parser_recurse_merge(): 
 */
int parser(t_base *base)
{
	base->parser = parser_cmd(base->lexer);
	if (base->parser == NULL)
		return (0);
	if (parser_recursive_merge(&base->parser) == ERROR)
	{
		return (0);
	}
	return (1);
}
















// int	parser_scmd_set(t_parser *new, t_lexer *lexer)
// {
// 	t_lexer	*next;

// 	while (parser_cmd_type(lexer) == CMD_SCMD)
// 	{
// 		next = lexer->next;
// 		if (lexer->flag & TOK_REDIR)
// 		{
// 			if (redir_type(lexer->str) == REDIR_HEREDOC)
// 			{
// 				if (parser_heredoc(lexer) == ERROR)
// 					return (ERROR);
// 			}
// 			redir_lstadd(&new->redir, lexer);
// 		}
// 		else if (lexer->flag & TOK_REDIR_FILE)
// 			redir_lstadd(&new->redir, lexer);
// 		else
// 			argv_lstadd(&new->argv, lexer);
// 		lexer->next = NULL;
// 		lexer = next;
// 	}
// 	return (0);
// }

// t_parser	*parser_cmd_create(t_base *base, int type)
// {
// 	t_parser	*new;
// 	t_parser	*tmp;

// 	new = (t_parser *)malloc(sizeof(t_parser));
// 	if (!new)
// 		return (NULL);
// 	new->type = type;
// 	new->argv = NULL;
// 	new->redir = NULL;
// 	new->next = NULL;
// 	if (base->parser == NULL)
// 	{
// 		base->parser = new;
// 		base->parser->next = NULL;
// 	}
// 	else
// 	{
// 		tmp = base->parser;
// 		while (tmp->next != NULL)
// 			tmp = tmp->next;
// 		tmp->next = new;
// 	}
// 	return (new);
// }

// /** OK:
//  * @brief Lexer'deki tokenlerden cmd tipini donduruyor.
//  * 
//  * NOTE: Text ya da redir(< >) tipindeyse scmd donuyor.
//  * 
//  * @param lexer 
//  * @return int 
//  */
// int	parser_cmd_type(t_lexer *lexer)
// {
// 	if (lexer == NULL)
// 		return (ERROR);
// 	else if (lexer->flag & (TOK_TEXT | TOK_REDIR))
// 		return (CMD_SCMD);
// 	else if (lexer->flag & TOK_BIN_OP)
// 	{
// 		if (lexer->str[0] == '&')
// 			return (CMD_AND);
// 		else if (lexer->str[0] == '|')
// 			return (CMD_OR);
// 	}
// 	else if (lexer->str[0] & TOK_PIPE)
// 		return (CMD_PIPE);
// 	else if (lexer->str[0] & TOK_O_BRACKET)
// 		return (CMD_O_BRACKET);
// 	else if (lexer->str[0] & TOK_C_BRACKET)
// 		return (CMD_C_BRACKET);
// 	return (ERROR);
// }


// int	parser_cmd(t_base *base)
// {
// 	t_lexer		*tmp;
// 	t_parser	*new;

// 	tmp = base->lexer;
// 	while (tmp)
// 	{
// 		new = parser_cmd_create(base, parser_cmd_type(tmp));
// 		if (new == NULL || (new->type == CMD_SCMD && parser_scmd_set(new, tmp) == ERROR))
// 		{
// 			printf("1.HATA\n");
// 			return (ERROR);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (1);
// }

// int	parser(t_base *base)
// {
// 	if (parser_cmd(base) <= 0)
// 		return (0);
// 	return (0);
// }


