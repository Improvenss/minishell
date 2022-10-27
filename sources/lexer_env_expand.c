/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:50:31 by gsever            #+#    #+#             */
/*   Updated: 2022/10/27 10:11:28 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_it_expand(t_base *base, int status)
{
	t_lexer	*last;

	last = lexer_lstlast(base->lexer);
	if (last && last->flag & status)
		return (1);
	return (0);
}

char	*env_expand_seperate_third(t_base *base, char *env_name)
{
	char *str;

	if (is_it_expand(base, TOK_HEREDOC))
	{
		str = ft_strjoin("$", env_name);
		return (str);
	}
	else
		str = env_findret(base, env_name);
	if (!str)
	{
		free(str);
		if (is_it_expand(base, (TOK_REDIR | TOK_HEREDOC)))
			str = ft_strjoin("$", env_name);
		else
			str = ft_strdup("");
		return (str);
	}
	return (str);
}

char	*env_expand_next_next(t_base *base, char *token, int *i, char *new)
{
	int		l;
	char	*env_name;
	char	*str;

	l = (*i);
	while (token[*i] && token[*i] != '$' && !ft_strchr(WHITESPACES, token[*i]))
		(*i)++;
	env_name = ft_substr(token, l, *i - l);
	str = env_expand_seperate_third(base, env_name);
	free(env_name);
	if (new != NULL && str != NULL)
	{
		base->mem_1 = ft_strjoin(new, str);
		free(new);
		free(str);
		return (base->mem_1);
	}
	if (new == NULL && str != NULL)
		return (str);
	return (new);
}

char	*env_expand_seperate_second(t_base *base, char *new)
{
	if (new == NULL)
		return (ft_strdup("$"));
	else
	{
		base->mem_1 = new;
		base->mem_2 = ft_strjoin(new, "$");
		free(base->mem_1);
		return (base->mem_2);
	}
	return (new);
}

char	*env_expand_next(t_base *base, char *token, int *i, char *new)
{
	(*i)++;
	if (token[*i] == '\0')
	{
		return (env_expand_seperate_second(base, new));
	}
	if (token[*i] == '?')
	{
		(*i)++;
		if (new == NULL)
			return (ft_itoa(exit_status(0, 1)));
		else
		{
			base->mem_1 = ft_itoa(exit_status(0, 1));
			base->mem_2 = ft_strjoin(new, base->mem_1);
			free(base->mem_1);
			free(new);
			return (base->mem_2);
		}
	}
	if (ft_strchr(WHITESPACES, token[*i]))
	{
		(*i)++;
		return (ft_chrjoin("$", token[*i]));
	}
	return (env_expand_next_next(base, token, i, new));
}

static void	env_expand_seperate_first(t_base *base,
	char **new, char *token, int *i)
{
	while (token[*i] == '$' && token[*i + 1] == '$')
	{
		*i = *i + 2;
		if (*new == NULL)
			*new = ft_strdup("$");
		else
		{
			base->mem_1 = *new;
			*new = ft_strjoin(*new, "$");
			free(base->mem_1);
		}
	}
}

char	*env_expand(t_base *base, char *token, int i, int l)
{
	char	*new;

	new = NULL;
	while (token[i])
	{
		l = i;
		while (token[i] != '$' && token[i])
			i++;
		if (i > 0 && new == NULL)
			new = ft_substr(token, 0, i);
		else if (i > l)
		{
			base->mem_1 = ft_substr(token, l, i - l);
			base->mem_2 = new;
			new = ft_strjoin(new, base->mem_1);
			free(base->mem_1);
			free(base->mem_2);
		}
		env_expand_seperate_first(base, &new, token, &i);
		if (token[i] == '$')
			new = env_expand_next(base, token, &i, new);
	}
	free(token);
	return (new);
}
