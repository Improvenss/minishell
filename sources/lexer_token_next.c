/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:45:06 by gsever            #+#    #+#             */
/*   Updated: 2022/10/05 15:45:33 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Diger operatorlarin arasindaki uzunlugu icin.
 * 
 * @param chr 
 * @return int 
 */
static int	other_len(char *chr)
{
	if (*chr == '(' || *chr == ')')
		return (1);
	else if (*chr == '<' && *(chr + 1) != '<')
		return (1);
	else if (*chr == '<' && *(chr + 1) == '<')
		return (2);
	else if (*chr == '>' && *(chr + 1) != '>')
		return (1);
	else if (*chr == '>' && *(chr + 1) == '>')
		return (2);
	else if (*chr == '|' && *(chr + 1) != '|')
		return (1);
	else if (*chr == '|' && *(chr + 1) == '|')
		return (2);
	else if (*chr == '&' && *(chr + 1) == '&')
		return (2);
	return (0);
}

/**
 * @brief Tirnak arasi uzunlugu donduruyor.
 * 
 * @param str 
 * @fn ft_strchr()
 * @fn print_error()
 * @return int 
 */
static int	quote_len(char *str)
{
	char	mark;
	int		i;

	if (str == NULL || *str == '\0')
		return (0);
	if (ft_strchr(QUOT_MARKS, str[0]) == NULL)
		return (0);
	mark = str[0];
	i = 0;
	while (str[++i])
	{
		if (str[i] == mark)
			break ;
	}
	if (str[i] != mark)
	{
		print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_QUOTE);
		return (ERROR);
	}
	return (i + 1);
}

/**
 * @brief Tirnak varsa tirnaklari token olarak yaziyor.
 * 
 * @param str 
 * @param i 
 * @param l_token 
 * @fn quote_len() Tirnak arasi uzunlugu hesaplatmak icin.
 * @fn print_error()
 * @fn strerror()
 * @fn token_create() Yeni list olusturup tokeni list'e yaziyor.
 * @fn ft_lstadd_back() Tokenli list'i alip list'in sonuna ekliyor.
 * @fn ft_strchr()
 * @fn other_len()
 * @fn token_content()
 * @return int 
 */
int	lexer_token_quote(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;
	int		len;

	len = quote_len(&str[*i]);
	if (len == ERROR)
		return (ERROR);
	if (len > 0)
	{
		token_str = ft_substr(str, *i + 1, len - 2);
		if (token_str == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		if (str[*i] == '\'')
			token = token_create(token_str, TOK_TEXT | TOK_S_QUOTE);
		else
			token = token_create(token_str, TOK_TEXT | TOK_D_QUOTE);
		if (token == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		ft_lstadd_back(l_token, token);
		*i += len;
		if (!ft_strchr(WHITESPACES, str[*i]) && other_len(&str[*i]) == 0)
			token_content(token)->flags |= TOK_CONNECTED;
	}
	return (0);
}

/**
 * @brief WHITESPACES, QUOT_MARKS ve other_len harici bir karakter
 *  varsa patlatiyor, yoksa text'in uzunlugunu donduruyor.
 * 
 * @param str 
 * @fn ft_strchr()
 * @fn other_len()
 * @return int -> text_len
 */
static int	text_len(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr(WHITESPACES, str[i]))
			break ;
		else if (other_len(&str[i]) > 0)
			break ;
		else if (ft_strchr(QUOT_MARKS, str[i]))
			break ;
	}
	return (i);
}

/**
 * @brief TEXT -> -Shell Operators-
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
 * @fn ft_strchr()
 * @fn other_len()
 * @fn token_content()
 * @return int -> ERROR: -1, OK: 0
 */
int	lexer_token_text(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;
	int		len;

	len = text_len(&str[*i]);
	if (len > 0)
	{
		token_str = ft_substr(str, *i, len);
		if (token_str == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		token = token_create(token_str, TOK_TEXT);
		if (token == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		ft_lstadd_back(l_token, token);
		*i += len;
		if (!ft_strchr(WHITESPACES, str[*i]) && other_len(&str[*i]) == 0)
			token_content(token)->flags |= TOK_CONNECTED;
	}
	return (0);
}
