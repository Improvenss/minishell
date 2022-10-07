/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:19:51 by gsever            #+#    #+#             */
/*   Updated: 2022/10/07 14:13:07 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief REDIR islemlerini yapiyor.
 * 
 * @param l_token 
 * @return int 
 */
static int	redir_mark_files(t_list *l_token)
{
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_REDIR)
		{
			if (l_token->next == NULL
				|| !(token_content(l_token->next)->flags & TOK_TEXT))
			{
				print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_REDIR);
				return (ERROR);
			}
			l_token = l_token->next;
			token_content(l_token)->flags |= TOK_REDIR_FILE;
			while (token_content(l_token)->flags & TOK_CONNECTED)
			{
				token_content(l_token->next)->flags |= TOK_REDIR_FILE;
				l_token = l_token->next;
			}
		}
		l_token = l_token->next;
	}
	return (0);
}

/**
 * @brief Tokenlerini -> Lexerleme asamasi.
 * Icerigini degistirebilmek icin &'yle gonderip *'la almis.
 * @param input 
 * @fn lexer_token_bin_op()
 * @fn ft_strchr() WHITESPACES: ile bosluklari falan geciyor.
 * @return t_list* 
 */
static t_list	*token_list_get(char *input)
{
	t_list	*l_token;
	int		i;

	l_token = NULL;
	i = -1;
	while (input && input[++i])
	{
		if (lexer_token_bin_op(input, &i, &l_token) == ERROR)
			break ;
		if (lexer_token_pipe(input, &i, &l_token) == ERROR)
			break ;
		if (lexer_token_bracket(input, &i, &l_token) == ERROR)
			break ;
		if (lexer_token_redir(input, &i, &l_token) == ERROR)
			break ;
		if (lexer_token_text(input, &i, &l_token) == ERROR)
			break ;
		if (lexer_token_quote(input, &i, &l_token) == ERROR)
			break ;
		while (input[i] && ft_strchr(WHITESPACES, input[i]))
			i++;
	}
	if (input[i] != '\0')
		ft_lstclear(&l_token, new_token_destroy);
	return (l_token);
}

/**
 * @brief Adim 1: -LEXER-
 * 
 * @param input 
 * @fn token_list_get() inputtaki girdinin tokenlerini aliyor.
 * @return t_list* 
 */
t_list	*lexer(char *input)
{
	t_list	*l_token;

	l_token = token_list_get(input);
	if (l_token == NULL)
		return (NULL);
	if (lexer_syntax_check(l_token) == ERROR)
	{
		exec_exit_status_set(ERR_SYNTAX_EXIT);
		ft_lstclear(&l_token, new_token_destroy);
		return (NULL);
	}
	if (redir_mark_files(l_token) == ERROR)
	{
		exec_exit_status_set(ERR_SYNTAX_EXIT);
		ft_lstclear(&l_token, new_token_destroy);
		return (NULL);
	}
	return (l_token);
}
