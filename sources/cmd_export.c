/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:55:13 by gsever            #+#    #+#             */
/*   Updated: 2022/10/04 16:15:21 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		cmd_export_add(t_base *base)
{
	t_env	*tmp;
	t_env	*new;
	int		i;
	
	i = 1;
	while (base->array_line[i])
	{
		if (export_same_check(base, base->array_line[i]))
		{
			new = (t_env *)malloc(sizeof(t_env));
			new->data = ft_split(base->array_line[i], '=');
			if (base->array_line[i][ft_strlen(base->array_line[i]) - 1] == '=')
				new->data[1] = "";
			tmp = base->env;
			while (tmp->next->next != NULL)
				tmp = tmp->next;
			new->next = tmp->next;
			tmp->next = new;
		}
		i++;
	}
	return (0);
}

void	cmd_export_print(t_base *base)
{
	t_env	*tmp_down;
	char	*str;
	char	*print;
	int		i;

	i = export_lstsize(base->env);
	print = export_find_min_str(base);
	while (i-- > 0)
	{
		str = env_findret(base, print);
		if (ft_strcmp_edited(print, "_"))
		{
			if (str == NULL)
				printf("declare -x %s\n", print);
			else
				printf("declare -x %s=%c%s%c\n", print, '"', str, '"');
		}
		str = export_find_max_str(base);
		tmp_down = base->env;
		while (tmp_down != NULL)
		{
			if (ft_strcmp_edited(print, tmp_down->data[0]) < 0 
			&& ft_strcmp_edited(str, tmp_down->data[0]) > 0)
				str = tmp_down->data[0];
			tmp_down = tmp_down->next;
		}
		print = str;
	}
}

int	cmd_export(t_base *base)
{
	if (base->array_line[1] == NULL)
		cmd_export_print(base);
	else if (export_arg_check(base->array_line))
		cmd_export_add(base);
	return (0);
}
