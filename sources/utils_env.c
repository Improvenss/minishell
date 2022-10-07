/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:19:35 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/06 21:08:32 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_env(t_base *base, char *env_name, char *new_str)
{
	t_env	*tmp;
	int		exit;

	exit = 0;
	tmp = base->env;
	while (tmp != NULL && exit == 0)
	{
		if (ft_strcmp_edited(env_name, tmp->data[0]) == 0)
		{
			tmp->data[1] = new_str;
			exit = 1;
		}
		tmp = tmp->next;
	}
}

char	*env_findret(t_base *base, char *env_name)
{
	t_env	*tmp;

	tmp = base->env;
	while (tmp != NULL)
	{
		if (ft_strcmp_edited(env_name, tmp->data[0]) == 0)
			return (tmp->data[1]);
		tmp = tmp->next;
	}
	return (NULL);
}

int	env_struct(t_base *base, char *new_arg)
{
	t_env	*new;
	t_env	*temp;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (ERROR);
	new->data = ft_split(new_arg, '=');
	new->next = NULL;
	if (base->env == NULL)
	{
		base->env = new;
		base->env->next = NULL;
	}
	else
	{
		temp = base->env;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}
