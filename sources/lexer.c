/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:23:40 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/13 10:23:40 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lexer_syntax(t_lexer *lexer)
{
	while (lexer)
	{
		if (lexer->flag == TOK_REDIR || lexer->flag == TOK_HEREDOC)
		{
			if (lexer->next == NULL || !(lexer->next->flag & (TOK_TEXT | TOK_D_QUOTE | TOK_S_QUOTE | TOK_REDIR_FILE))
			||	lexer->next->flag & (TOK_REDIR | TOK_HEREDOC))
				return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_REDIR)); // aa >'\0' veya a >>>'\0' veya a <<< b'\0'
		}
		if (lexer->flag == TOK_PIPE)
			if (lexer->next == NULL || !(lexer->next->flag & (TOK_TEXT | TOK_D_QUOTE | TOK_S_QUOTE)) || lexer->prev == NULL)
				return (print_error(SHELLNAME, ERR_SYNTAX, NULL, ERR_PIPE));
		lexer = lexer->next;
	}
	return (0);
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
		new->prev = NULL;
	}
	else
	{
		temp = base->lexer;
		while (temp->next != NULL)
			temp = temp->next;
		new->prev = temp;
		temp->next = new;
	}
	return (new);
}

int	lexer_pipe(t_base *base, char *str, int *i)
{
	char *token;
	t_lexer	*new;

	if (str[*i] == '|' && str[*i + 1] != '|' && str[*i - 1] != '|')
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

int	redir_type(char *token)
{
	if (ft_strncmp_edited(token, "<", 1))
		return (TOK_REDIR);
	if (ft_strncmp_edited(token, ">", 1))
		return (TOK_REDIR);
	if (ft_strncmp_edited(token, "<<", 2))
		return (TOK_HEREDOC);
	if (ft_strncmp_edited(token, ">>", 2))
		return (TOK_HEREDOC);
	return (1);
}

int	lexer_redir(t_base *base, char *str, int *i)
{
	char 	*token;
	int		len;
	t_lexer *new;

	len = 0;
	while (ft_isdigit(str[*i + len])) // 1 > 1.txt
		len++;
	if (str[*i + len] == '<' || str[*i + len] == '>')
	{
		if (str[*i + len] == str[*i + len + 1])
			len++;
		len++;
		token = ft_substr(str, *i, len);
		if(!token)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		new = token_create(base, token, redir_type(token));//TOK_REDIR);
		if (!new)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		*i = *i + len;
	}
	return (0);
}

static int other_lenght(char *str)
{
	if (*str == '<' && *(str + 1) != '<')
		return (1);
	else if (*str == '<' && *(str + 1) == '<')
		return (2);
	else if (*str == '>' && *(str + 1) != '>')
		return (1);
	else if (*str == '>' && *(str + 1) == '>')
		return (2);
	else if (*str == '|' && *(str + 1) != '|' && *(str - 1) != '|')
		return (1);
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

char	*env_expand_next_next(t_base *base, char *token, int *i, char *new)
{
	int		l;
	char	*env_name;
	char	*str;

	l = (*i);
	while (token[*i] && token[*i] != '$')
		(*i)++;
	env_name = ft_substr(token, l, *i - l);
	//free(token);
	if (!env_name)
		return ("");
	str = env_findret(base, env_name);
	//free(env_name);
	//printf("...%s\n", str);
	if (new != NULL && str != NULL)
		return (ft_strjoin(new, str));
	if (new != NULL && str == NULL)
		return (new);
	if (new == NULL && str != NULL)
		return (str);
	return ("");
}

char	*env_expand_next(t_base *base, char *token, int *i, char *new)
{
	(*i)++;
	if (token[*i] == '\0')
	{
		if (new == NULL)
			return ("$");
		else
			return (ft_strjoin(new, "$"));
	}
	if (token[*i] == '?')
	{
		(*i)++;
		if (new == NULL)
			return (ft_itoa(g_status));
		else
			return(ft_strjoin(new, ft_itoa(g_status)));
	}
	return (env_expand_next_next(base, token, i, new));
}

char	*env_expand(t_base *base, char *token)
{
	int		i;
	int		l;
	char	*new;

	i = 0;
	new = NULL;
	while (token[i])
	{
		l = i;
		while (token[i] != '$' && token[i])
			i++;
		if (i > 0 && new == NULL)
			new = ft_substr(token, 0, i);
		else if (i > l)
			new = ft_strjoin(new, ft_substr(token, l, l + i));
		while (token[i] == '$' && token[i + 1] == '$')
		{
			i = i + 2;
			if (new == NULL)
				new = ft_strdup("2840"); // hata aldığından dolayı strdup <3
			else
				new = ft_strjoin(new, "2840");
		}
		if (token[i] == '$')
			new = env_expand_next(base, token, &i, new);
	}
	//printf("#%11s#\n", new);
	return (new);
}

t_lexer	*lexer_lstlast(t_lexer *lexer)
{
	t_lexer *tmp;

	if (lexer == NULL)
		return (NULL);
	tmp = lexer;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void node_merge(t_lexer **lexer, char *token, char *str, int *i)
{
	char	*tmp;
	if (!ft_strchr(WHITESPACES, str[*i]) && other_lenght(&str[*i]) == 0)
		(*lexer)->flag = TOK_CONNECTED + TOK_TEXT;
	else if ((*lexer)->prev && (*lexer)->prev->flag & (TOK_REDIR | TOK_HEREDOC)) //"AHMETKARACA" > "42"'MAHMUT'$PWD
	  	(*lexer)->flag = TOK_REDIR_FILE;
	else
		(*lexer)->flag = TOK_TEXT;
	tmp = ft_strjoin((*lexer)->str, token);
	free((*lexer)->str);
	free(token);
	(*lexer)->str = tmp;
}

int	lexer_type(t_lexer *last, int type)
{
	if (last != NULL && (last->flag == TOK_REDIR || last->flag == TOK_HEREDOC))
		return (TOK_REDIR_FILE);
	return (type);
}

int	lexer_text(t_base *base, char *str, int *i)
{
	char 	*token;
	int		len;
	t_lexer *new;
	t_lexer	*last;

	len = text_lenght(&str[*i]);
	if (len > 0)
	{
		token = ft_substr(str, *i, len);
		if (ft_strchr(token, '$'))
			token = env_expand(base, token);
		last = lexer_lstlast(base->lexer);
		if (last && last->flag & TOK_CONNECTED)
		{
			*i = *i + len;
			node_merge(&last, token, str, i);
			return (0);
		}
		// if (token[0] == '\0') //pipelar arası argüman gerekli olduğundan dolayı kapattım.(boş argüman olsada lazım)
		// {
		// 	*i = *i + len;
		// 	return (0);
		// }
		if(!token)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		new = token_create(base, token, lexer_type(last, TOK_TEXT));//TOK_TEXT);
		if (!new)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		*i = *i + len;
		if (!ft_strchr(WHITESPACES, str[*i]) && other_lenght(&str[*i]) == 0)
			new->flag |= TOK_CONNECTED;
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
	t_lexer	*last;

	len = quote_lenght(&str[*i]);
	if (len == ERROR)
		return (ERROR);
	if (len > 0)
	{
		token = ft_substr(str, *i + 1, len - 2);
		if (ft_strchr(token, '$') && str[*i] == '"')
			token = env_expand(base, token);
		last = lexer_lstlast(base->lexer);
		if (last && last->flag & TOK_CONNECTED)
		{
			*i = *i + len;
			node_merge(&last, token, str, i);
			return (0);
		}
		// if (token[0] == '\0')
		// {
		// 	*i = *i + len;
		// 	return (0);
		// }
		if(!token)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		if (str[*i] == '\'')
			new = token_create(base, token, lexer_type(last, TOK_TEXT + TOK_S_QUOTE));//TOK_TEXT + TOK_S_QUOTE);
		else
			new = token_create(base, token, lexer_type(last, TOK_TEXT + TOK_D_QUOTE));//TOK_TEXT + TOK_D_QUOTE);
		if (!new)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		*i = *i + len;
		if (!ft_strchr(WHITESPACES, str[*i]) && other_lenght(&str[*i]) == 0)
			new->flag |= TOK_CONNECTED;
	}
	return (0);
}

void	lexer(t_base *base, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (lexer_pipe(base, str, &i) == ERROR)
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
	if (str[i] != '\0')
		g_status = 1;
	debug_print_str(base, "DEBUG", "print");
}
