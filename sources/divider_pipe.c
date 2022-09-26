/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divider_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:37:09 by akaraca           #+#    #+#             */
/*   Updated: 2022/09/26 20:12:51 by akaraca          ###   ########.fr       */
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

char	*pipe_to_pipe(char *str, int *l)
{
	char	*new;
	int		x;
	int		y;
	int		k;

	y = *l;
	k = 0;
	x = 0;
	while (str[y] && str[y] == '|')
		y++;
	k = word_counter(str, y);
	new = (char *)malloc(sizeof(char) * k);
	while (x < k)
	{
		new[x] = str[y];
		x++;
		y++;
	}
	new[x] = '\0';
	//printf("new[%d]: #%s#\n", x, new);
	*l = y;
	return (new);
}

char	**divider(char *str)
{
	char **tmp;
	int	l;
	int	i;
	int	pipe_count;

	pipe_count = divider_pipe_counter(str);
	tmp = (char **)malloc(sizeof(char) * pipe_count);
	i = 0;
	l = 0;
	while (i < pipe_count)
	{
		tmp[i] = pipe_to_pipe(str, &l);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}
