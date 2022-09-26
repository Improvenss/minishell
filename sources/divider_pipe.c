/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divider_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:37:09 by akaraca           #+#    #+#             */
/*   Updated: 2022/09/26 17:53:37 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	divider_pipe_counter(char *str)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] != '|' && str[i - 1] != '|')
			count++;
		i++;
	}
	// printf("pipe_count: %d\n", count);
	return (count);
}

int word_counter(char *str, int i)
{
	int	l;

	l = 0;
	while (str[i] && str[i] != '|')
	{
		if (str[i + 1] == '|' && str[i + 2] == '|')
		{
			i = i + 2;
			l = l + 2;
		}
		i++;
		l++;
	}
	// printf("word_count: %d\n", l);
	return (l);
}

void	pipe_to_pipe(char **new, char *str, int pipe_count)
{
	int	i;
	int	l;
	int	k;
	int	x;

	l = -1;
	x = 0;
	while (++l < pipe_count)
	{
		i = 0;
		k = word_counter(str, x);
		new[l] = (char *)malloc(sizeof(char) * k);
		while (i < k)
		{
			new[l][i] = str[x];
			i++;
			x++;
		}
		new[l][i] = '\0';
		// printf("new[%d]: #%s#\n", l, new[l]);
		while (str[x] && str[x] == '|')
			x++;
	}
	new[l] = NULL;
}

char	**divider(char *str)
{
	char	**new;
	int		pipe_count;
	
	pipe_count = divider_pipe_counter(str);
	new = (char **)malloc(sizeof(char *) * pipe_count + 1);
	if (!new)
		return (NULL);
	pipe_to_pipe(new, str, pipe_count);
	return (new);
}
