/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:19:53 by gsever            #+#    #+#             */
/*   Updated: 2022/10/04 17:28:52 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_unset(t_base *base)
{
	t_env	*tmp;
	t_env	*before;
	t_env	*del;
	int		l;

	l = 0;
	while (base->array_line[++l] != NULL)
	{
		tmp = base->env;
		tmp->prev = NULL;
		while (tmp != NULL && base->array_line[l] != NULL)
		{
			if (ft_strcmp_edited(base->array_line[l], tmp->data[0]) == 0)
			{
				del = tmp;
				tmp->prev->next = tmp->next;
				free(del->data);
			}
			before = tmp;
			tmp = tmp->next;
			if (tmp != NULL)
				tmp->prev = before;
		}
	}
	return (0);
}
