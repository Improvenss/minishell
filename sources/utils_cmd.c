/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:22:13 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/27 08:56:23 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** NORMOK:
 * @file utils_cmd.c
 * @author Ahmet KARACA (akaraca)
 * @author Görkem SEVER (gsever)
 * @brief 
 * @version 0.1
 * @date 2022-10-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../includes/minishell.h"

void	close_cmd_fd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->infile != 0)
			close(tmp->infile);
		if (tmp->outfile != 1)
			close(tmp->outfile);
		tmp = tmp->next;
	}
}

int	cmd_count(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = cmd;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*str_add(char *tmp, char *str)
{
	char	*mem_1;
	char	*mem_2;

	mem_1 = ft_strjoin(str, "\n");
	if (tmp == NULL)
		return (mem_1);
	mem_2 = ft_strjoin(tmp, mem_1);
	free(mem_1);
	if (tmp != NULL)
		free(tmp);
	return (mem_2);
}

void	cmd_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = *lst;
	if (*lst)
	{
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
	else
	{
		new->prev = NULL;
		*lst = new;
	}
}
