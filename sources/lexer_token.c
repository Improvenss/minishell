/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:37:18 by gsever            #+#    #+#             */
/*   Updated: 2022/10/05 14:45:24 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer_token.c
 * @author Ahmet KARACA (akaraca)
 * @author Gorkem SEVER (gsever)
 * @brief Shell operatorlerini bulup token olarak aliyor.
 * @version 0.1
 * @date 2022-10-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../includes/minishell.h"

/**
 * @brief BRACKETS -> -Shell Operators-
 * 
 * '(' ')' operatorlerini bulup token olarak aliyor. (ayri ayri)
 * 
 * @note TOK_O_BRACKET: Open bracket.
 * @note TOK_C_BRACKET: Close bracket.
 * 
 * @param str input(terminal girdisi)
 * @param i input[i](girdinin indexi)
 * @param l_token Main token list.
 * @fn ft_isdigit() 
 * @fn ft_substr() str'nin icerisinde verilen i(start)'in len(len)
 *  kadarini donduruyor.
 * @fn print_error() -1 donduruyor.
 * @fn strerror()
 * @fn token_create() Yeni list olusturup tokeni list'e yaziyor.
 * @fn ft_lstadd_back() Tokenli list'i alip list'in sonuna ekliyor.
 * @return int -> ERROR: -1, OK: 0
 */
int	lexer_token_redir(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;
	int		len;

	len = 0;
	while (ft_isdigit(str[*i + len]))
		len++;
	if (str[*i + len] == '<' || str[*i + len] == '>')
	{
		if (str[*i + len] == str[*i + len + 1])
			len++;
		len++;
		token_str = ft_substr(str, *i, len);
		if (token_str == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		token = token_create(token_str, TOK_REDIR);
		if (token == NULL)
		{
			free(token_str);
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, token);
		*i += len;
	}
	return (0);
}

/**
 * @brief BRACKETS -> -Shell Operators-
 * 
 * '(' ')' operatorlerini bulup token olarak aliyor. (ayri ayri)
 * 
 * @note TOK_O_BRACKET: Open bracket.
 * @note TOK_C_BRACKET: Close bracket.
 * 
 * @param str input(terminal girdisi)
 * @param i input[i](girdinin indexi)
 * @param l_token Main token list.
 * @fn ft_substr() str'nin icerisinde verilen i(start)'in len(1)
 *  kadarini donduruyor.
 * @fn print_error() -1 donduruyor.
 * @fn strerror()
 * @fn token_create() Yeni list olusturup tokeni list'e yaziyor.
 * @fn ft_lstadd_back() Tokenli list'i alip list'in sonuna ekliyor.
 * @return int -> ERROR: -1, OK: 0
 */
int	lexer_token_bracket(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;

	if (str[*i] == '(' || str[*i] == ')')
	{
		token_str = ft_substr(str, *i, 1);
		if (token_str == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		if (str[*i] == '(')
			token = token_create(token_str, TOK_O_BRACKET);
		else
			token = token_create(token_str, TOK_C_BRACKET);
		if (token == NULL)
		{
			free(token_str);
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, token);
		(*i)++;
	}
	return (0);
}

/**
 * @brief PIPE -> -Shell Operator-
 * 
 * '|' operatorunu bulup token olarak aliyor. (tekli)
 * 
 * @param str input(terminal girdisi)
 * @param i input[i](girdinin indexi)
 * @param l_token Main token list.
 * @fn ft_substr() str'nin icerisinde verilen i(start)'in len(1)
 *  kadarini donduruyor.
 * @fn print_error() -1 donduruyor.
 * @fn strerror()
 * @fn token_create() Yeni list olusturup tokeni list'e yaziyor.
 * @fn ft_lstadd_back() Tokenli list'i alip list'in sonuna ekliyor.
 * @return int -> ERROR: -1, OK: 0
 */
int	lexer_token_pipe(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;

	if (str[*i] == '|')
	{
		token_str = ft_substr(str, *i, 1);
		if (token_str == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		token = token_create(token_str, TOK_PIPE);
		if (token == NULL)
		{
			free(token_str);
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, token);
		(*i)++;
	}
	return (0);
}

/**
 * @brief BIN_OP -> -Shell Operators-
 * 
 * && ve || operatorlerini bulup token olarak aliyor. (2'li olanlar)
 * 
 * @param str input(terminal girdisi)
 * @param i input[i](girdinin indexi)
 * @param l_token Main token list.
 * @fn ft_substr() str'nin icerisinde verilen i(start)'in len(2)
 *  kadarini donduruyor.
 * @fn print_error() -1 donduruyor.
 * @fn strerror()
 * @fn token_create() Yeni list olusturup tokeni list'e yaziyor.
 * @fn ft_lstadd_back() Tokenli list'i alip list'in sonuna ekliyor.
 * @return int -> ERROR: -1, OK: 0
 */
int	lexer_token_bin_op(char *str, int *i, t_list **l_token)
{
	t_list	*new_token;
	char	*token_str;

	if ((str[*i] == '&' && str[*i + 1] == '&')
		|| (str[*i] == '|' && str[*i + 1] == '|'))
	{
		token_str = ft_substr(str, *i, 2);
		if (token_str == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		new_token = token_create(token_str, TOK_BIN_OP);
		if (new_token == NULL)
		{
			free(token_str);
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, new_token);
		*i += 2;
	}
	return (0);
}
