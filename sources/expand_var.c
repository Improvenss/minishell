/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:40:21 by gsever            #+#    #+#             */
/*   Updated: 2022/10/13 13:28:15 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 * @param base 
 * @param exp_str 
 * @fn ft_itoa()
 * @fn print_error(): RETURN: ERROR -> -1
 * @fn strerror(): Integer error number to string converter.
 * @fn str_append_str(): Eklemek dahil etmek anlaminda 
 * @fn free()
 * @return int 
 */
static int	expanded_str_append_exit_code(t_base *base, char **exp_str)
{
	char	*exit_str;

	exit_str = ft_itoa(base->exit_status);
	if (exit_str == NULL)
		return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
	*exp_str = str_append_str(*exp_str, exit_str);
	free(exit_str);
	if (*exp_str == NULL)
		return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
	return (0);
}

static int	expanded_str_get(t_lexer *token, char __unused **exp_str, int *i)
{
	if (token->str[*i] == '$' && token->str[*i + 1] == '?')
	{
		if (expanded_str_append_exit_code(token->base, exp_str) == ERROR)
			return (ERROR);
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