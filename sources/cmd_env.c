/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:48:48 by gsever            #+#    #+#             */
/*   Updated: 2022/10/04 16:13:38 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_env(t_base *base)
{
	t_env	*tmp;

	tmp = base->env;
	while (tmp != NULL)
	{
		if (tmp->data[1] == NULL)
			tmp->data[1] = "";
		if (ft_strcmp_edited(tmp->data[1], "") != 0)
			printf("%s=%s\n", tmp->data[0], tmp->data[1]);
		tmp = tmp->next;
	}
	return (0);
}
