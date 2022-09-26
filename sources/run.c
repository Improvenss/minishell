/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:10:15 by gsever            #+#    #+#             */
/*   Updated: 2022/09/26 09:58:06 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:41:13 by gsever            #+#    #+#             */
/*   Updated: 2022/09/23 00:23:55 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	divider_pipe_counter(char *str)
{
	int	count;
	int	i;
	
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] != '|' && str[i - 1] != '|')
			count++;
		i++;
	}
	return (count);
}

char	**divider(char *str, char c)
{
	int	i;
	int l;
	int	k;
	char	**tmp;

	printf("count:%d\n", divider_pipe_counter(str));
	tmp = (char **)malloc(sizeof(char *) * divider_pipe_counter(str));
	if (!tmp)
		return (NULL);
	i = 0;
	k = 0;
	printf("%d\n", __LINE__);
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
		{
			l = 0;
			i++;
			*tmp = (char *)malloc(sizeof(char) * i - k);
			while (k + l < i)
			{
				*tmp[l] = str[i];
				l++;
			}
			*tmp[l] = '\0';
			tmp++;
			k = i;
		}
		i++;
	}
	return (tmp);
}

void	command_run(t_base *base)
{	
	base->array_line = divider(base->input_line, '|');
	int i = 0;
	while (base->array_line[i])
	{
		printf("%d : %s.\n", i, base->array_line[i]);
		i++;
	}
	printf("Çalışıyor.\n");
}