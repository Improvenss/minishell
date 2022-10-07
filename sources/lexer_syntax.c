/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:25:48 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/07 14:32:08 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_brackets(t_lexer *lexer)
{
	int	count;

	count = 0;
	while (lexer)
	{
		if (lexer->flag == TOK_O_BRACKET)
		{
			count++;
			if (lexer->next && lexer->flag == TOK_C_BRACKET)
				return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_EMPTY_BRACKET));
		}
		else if (lexer->flag == TOK_C_BRACKET)
			count--;
		if (count < 0)
			return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_UNO_BRACKET));
		lexer = lexer->next;
	}
	if (count > 0)
		return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_UNC_BRACKET));
	return (0);
}

int	syntax_bin_op(t_lexer *lexer)
{
	if (lexer && lexer->flag == TOK_BIN_OP)
		return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_LIST)); // &&'\0' veya ||'\0' durumu için.
	while (lexer)
	{
		if (lexer->flag == TOK_BIN_OP)
		{
			if (lexer->next == NULL)
				return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_LIST)); // aaa&&'\0' durumu için.
			else if (lexer->next->flag == TOK_BIN_OP || lexer->next->flag == TOK_PIPE)
				return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_LIST)); //a&&||a'\0' durumu için
			else if	(lexer->next->flag == TOK_C_BRACKET)
				return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_LIST)); //(a&&)'\0' durumu için
		}
		if (lexer->flag == TOK_O_BRACKET)
		{
			if (lexer->next && lexer->next->flag == TOK_BIN_OP)
				return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_LIST)); //(&&a)'\0' durumu için.
		}
		lexer = lexer->next;
	}
	return (0);
}

int	syntax_pipe(t_lexer *lexer)
{
	if (lexer && lexer->flag == TOK_PIPE)
		return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_PIPE)); // |'\0' veya |A'\0'
	while (lexer)
	{
		if (lexer->flag == TOK_PIPE)
		{
			if (lexer->next == NULL)
				return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_PIPE)); // A|'\0'
			else if (lexer->next->flag == TOK_BIN_OP || lexer->next->flag == TOK_PIPE)
				return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_PIPE)); // a|&&a'\0' diğer durumu bulamadım :<
			else if (lexer->next->flag == TOK_C_BRACKET)
				return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_PIPE)); //(a|)'\0'
		}
		if (lexer->flag == TOK_O_BRACKET)
		{
			if (lexer->next && lexer->next->flag == TOK_PIPE)
				return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_PIPE)); // (A|)'\0'
		}
		lexer = lexer->next;
	}
	return (0);
}

int	syntax_missing_op(t_lexer *lexer)
{
	while (lexer)
	{
		if (lexer->flag == TOK_C_BRACKET && lexer->next
			&& lexer->next->flag == TOK_O_BRACKET)
			return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_MISS_OP)); // (aaa)(aaa)'\0'
		else if (lexer->flag == TOK_C_BRACKET && lexer->next)
			return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_MISS_OP)); // (aaa)a'\0'
		else if (lexer && lexer->next && lexer->next->flag == TOK_O_BRACKET)
			return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_MISS_OP)); //a(aaa)'\0'
		lexer = lexer->next;
	}
	return (0);
}

int	lexer_syntax(t_lexer *lexer)
{
	if (syntax_brackets(lexer) == ERROR)
		return (ERROR);
	if (syntax_bin_op(lexer) == ERROR)
		return (ERROR);
	if (syntax_pipe(lexer) == ERROR)
		return (ERROR);
	if (syntax_missing_op(lexer) == ERROR)
		return (ERROR);
	return (0);
}
