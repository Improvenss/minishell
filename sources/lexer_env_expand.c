/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:50:31 by gsever            #+#    #+#             */
/*   Updated: 2022/10/19 16:50:41 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*env_expand_next_next(t_base *base, char *token, int *i, char *new)
{
	int		l;
	char	*env_name;
	char	*str;

	l = (*i);
	while (token[*i] && token[*i] != '$')
		(*i)++;
	env_name = ft_substr(token, l, *i - l);
	if (!env_name)
		return (ft_strdup(""));
	str = env_findret(base, env_name);
	free(env_name);
	if (new != NULL && str != NULL)
	{
		base->mem_1 = ft_strjoin(new, str);
		free(new);
		return (base->mem_1);
	}
	if (new != NULL && str == NULL)
		return (new);
	if (new == NULL && str != NULL)
	{
		return (ft_strdup(str));
	}
	return (ft_strdup("")); //dup kullanılmaz ise hatalı olur.
}

char	*env_expand_next(t_base *base, char *token, int *i, char *new)
{
	(*i)++;
	if (token[*i] == '\0')
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
			return(base->mem_2);
		}
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
		{
			base->mem_1 = ft_substr(token, l, l + i);
			base->mem_2 = new;
			new = ft_strjoin(new, base->mem_1);
			free(base->mem_1);
			free(base->mem_2);
		}
		while (token[i] == '$' && token[i + 1] == '$')
		{
			i = i + 2;
			if (new == NULL)
				new = ft_strdup("777"); // hata aldığından dolayı strdup <3, hafızada yer açılmadan eşitlenme söz konusu ile freelenemez.
			else
			{
				base->mem_1 = new;
				new = ft_strjoin(new, "777");
				free(base->mem_1);
			}
		}
		if (token[i] == '$')
			new = env_expand_next(base, token, &i, new);
	}
	free(token);
	return (new);
}
