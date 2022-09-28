/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:37:09 by akaraca           #+#    #+#             */
/*   Updated: 2022/09/28 11:48:26 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	word_count(char *s)
{
	size_t	i;
	size_t	count;
	
	i = 0;
	count = 0;

	while (s[i])
	{
		if (s[i] == '|' && (s[i + 1] != '|' || s[i - 1] != '|'))
			count++;
		i++;
	}
	return (count);
}

char	*alloc(char *s)
{
	char	*new;
	int		i;

	i = 0;
	while (s[i] && (s[i] != '|' || (s[i] == '|' && (s[i - 1] == '|' || s[i + 1] == '|'))))
		i++;
	new = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] && (s[i] != '|' || (s[i] == '|' && (s[i - 1] == '|' || s[i + 1] == '|'))))
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**pipe_split(char *s)
{
	char	**new;
	int		wordc;
	int		l;
	int		i;

	wordc = word_count(s);
	new = (char **)malloc(sizeof(char *) * (wordc + 1));
	l = 0;
	i = 0;
	while (s[l])
	{
		while (s[l] && (s[l] == '|' && (s[l - 1] != '|' || s[l + 1] != '|')))
			l++;
		if (s[l])
		{
			new[i] = alloc(&s[l]);
			i++;
		}
		while (s[l] && (s[l] != '|' || (s[l] == '|' && (s[l - 1] == '|' || s[l + 1] == '|'))))
			l++;
	}
	new[i] = NULL;
	return (new);
}
