/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:48:48 by gsever            #+#    #+#             */
/*   Updated: 2022/10/04 17:18:24 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_env(t_base *base)
{
	t_env	*tmp;

	tmp = base->env;
	while (tmp != NULL)
	{
		if (tmp->data[1] != NULL)
			printf("%s=%s\n", tmp->data[0], tmp->data[1]);
		else if (tmp->is_env_equal && tmp->data[1] == NULL)
			printf("%s=\n", tmp->data[0]);
		tmp = tmp->next;
	}
	return (0);
}
