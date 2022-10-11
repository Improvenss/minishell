/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:57:01 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/10 14:11:21 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*token_to_str(t_lexer *lexer)
{
	char	*str;
	char	*tmp;

	if (lexer == NULL || lexer->str == NULL)
		return (NULL);
	str = ft_strdup(lexer->str);
	while (lexer && (lexer->flag & TOK_CONNECTED))
	{
		tmp = str;
		str = ft_strjoin(str, lexer->next->str);
		free(tmp);
		if (str == NULL)
			return (NULL);
		lexer = lexer->next;
	}
	return (str);
}

t_lexer *token_create(t_base *base, char *str, int type)
{
	t_lexer *new;
	t_lexer	*temp;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->flag = type;
	new->str = str;
	new->next = NULL;
	if (base->lexer == NULL)
	{
		base->lexer = new;
		base->lexer->next = NULL;
	}
	else
	{
		temp = base->lexer;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (new);
}

int	lexer_bin_op(t_base *base, char *str, int *i)
{
	char *token;
	t_lexer *new;

	if ((str[*i] == '&' && str[*i + 1] == '&')
		|| (str[*i] == '|' && str[*i + 1] == '|'))
	{
		token = ft_substr(str, *i, 2);
		if(!token)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		new = token_create(base, token, TOK_BIN_OP);
		if (!new)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		*i = *i + 2;
	}
	return (0);
}

int	lexer_pipe(t_base *base, char *str, int *i)
{
	char *token;
	t_lexer	*new;

	if (str[*i] == '|')
	{
		token = ft_substr(str, *i, 1);
		if(!token)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		new = token_create(base, token, TOK_PIPE);
		if(!new)
		{
			free(token);
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		}
		(*i)++;
	}
	return (0);
}

int	lexer_bracket(t_base *base, char *str, int *i)
{
	char *token;
	t_lexer *new;

	if (str[*i] == '(' || str[*i] == ')')
	{
		token = ft_substr(str, *i, 1);
		if(!token)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		if (str[*i] == '(')
			new = token_create(base, token, TOK_O_BRACKET);
		else
			new = token_create(base, token, TOK_C_BRACKET);
		if (!new)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		(*i)++;
	}
	return (0);
}

int	lexer_redir(t_base *base, char *str, int *i)
{
	char 	*token;
	int		len;
	t_lexer *new;

	len = 0;
	while (ft_isdigit(str[*i + len]))
		len++;
	if (str[*i + len] == '<' || str[*i + len] == '>')
	{
		if (str[*i + len] == str[*i + len + 1])
			len++;
		len++;
		token = ft_substr(str, *i, len);
		if(!token)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		new = token_create(base, token, TOK_REDIR);
		if (!new)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		*i = *i + len;
	}
	return (0);
}

static int other_lenght(char *str)
{
	if (*str == '(' || *str == ')')
		return (1);
	else if (*str == '<' && *(str + 1) != '<')
		return (1);
	else if (*str == '<' && *(str + 1) == '<')
		return (2);
	else if (*str == '>' && *(str + 1) != '>')
		return (1);
	else if (*str == '>' && *(str + 1) == '>')
		return (2);
	else if (*str == '|' && *(str + 1) != '|')
		return (1);
	else if (*str == '|' && *(str + 1) == '|')
		return (2);
	else if (*str == '&' && *(str + 1) == '&')
		return (2);
	return (0);
}

static int	text_lenght(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr(WHITESPACES, str[i]))
			break;
		else if (other_lenght(&str[i]) > 0)
			break;
		else if (ft_strchr(QUOTE_MARKS, str[i]))
			break;
	}
	return (i);
}

int	lexer_text(t_base *base, char *str, int *i)
{
	char 	*token;
	int		len;
	t_lexer *new;

	len = text_lenght(&str[*i]);
	if (len > 0)
	{
		token = ft_substr(str, *i, len);
		if(!token)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		new = token_create(base, token, TOK_TEXT);
		if (!new)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		*i = *i + len;
		if (!ft_strchr(WHITESPACES, str[*i]) && other_lenght(&str[*i]) == 0)
			new->flag |= TOK_CONNECTED;
			//new->flag = new->flag + TOK_CONNECTED;
	}
	return (0);
}

static int	quote_lenght(char *str)
{
	char	mark;
	int		i;

	if (!str || *str == '\0')
		return (0);
	if (ft_strchr(QUOTE_MARKS, str[0]) == NULL)
		return (0);
	mark = str[0];
	i = 0;
	while (str[++i])
		if (str[i] == mark)
			break;
	if (str[i] != mark)
	{
		print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_QUOTE);
		return (ERROR);
	}
	return (i + 1);
}

int	lexer_quote(t_base *base, char *str, int *i)
{
	char 	*token;
	int		len;
	t_lexer *new;

	len = quote_lenght(&str[*i]);
	if (len == ERROR)
		return (ERROR);
	if (len > 0)
	{
		token = ft_substr(str, *i + 1, len - 2);
		if(!token)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		if (str[*i] == '\'')
			new = token_create(base, token, TOK_TEXT | TOK_S_QUOTE);
		else
			new = token_create(base, token, TOK_TEXT | TOK_D_QUOTE);
		if (!new)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		*i = *i + len;
		if (!ft_strchr(WHITESPACES, str[*i]) && other_lenght(&str[*i]) == 0)
			new->flag |= TOK_CONNECTED;
			//new->flag = new->flag + TOK_CONNECTED;
	}
	return (0);
}

/**
 * @brief Operatorlerine gore Lexerleme islemi yapiliyor.
 * 
 * @param base 
 * @param str 
 */
void	lexer(t_base *base, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (lexer_bin_op(base, str, &i) == ERROR)
			break;
		if (lexer_pipe(base, str, &i) == ERROR)
			break;
		if (lexer_bracket(base, str, &i) == ERROR)
			break;
		if (lexer_redir(base, str, &i) == ERROR)
			break;
		if (lexer_text(base, str, &i) == ERROR)
			break;
		if (lexer_quote(base, str, &i) == ERROR)
			break;
		while (str[i] && ft_strchr(WHITESPACES, str[i]))
			i++;
	}
	t_lexer *tmp = base->lexer;
	while (tmp)
	{
		printf("%s %d\n", tmp->str, tmp->flag);
		tmp = tmp->next;
	}
}
