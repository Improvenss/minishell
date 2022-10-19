/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:41:34 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/15 21:41:34 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cmd_export.c
 * @author Ahmet KARACA (akaraca)
 * @author Gorkem SEVER (gsever)
 * @brief 
 * @version 0.1
 * @date 2022-08-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../includes/minishell.h"

int		cmd_export_add(t_base *base, t_cmd *cmd)
{
	t_env	*tmp;
	t_env	*new;
	int		i;
	
	i = 1;
	while (cmd->full_cmd[i])
	{
		if (export_same_check(base, cmd->full_cmd[i]))
		{
			new = (t_env *)malloc(sizeof(t_env));
			new->data = ft_split(cmd->full_cmd[i], '=');
			if (cmd->full_cmd[i][ft_strlen(cmd->full_cmd[i]) - 1] == '=')
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

void	cmd_export_print(t_base *base, t_cmd *cmd)
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
			int l = 0;
			write(cmd->outfile, "declare -x ", 12);
			while (print[l])
				write(cmd->outfile, &print[l++], 1);
			if (str != NULL)
			{
				l = 0;
				write(cmd->outfile, "\"", 1);
				while (str[l])
					write(cmd->outfile, &str[l++], 1);
				write(cmd->outfile, "\"", 1);
			}
			write(cmd->outfile, "\n", 1);
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

int	cmd_export(t_base *base, t_cmd *cmd)
{
	if (cmd->full_cmd[1] == NULL)
		cmd_export_print(base, cmd);
	else if (export_arg_check(cmd->full_cmd))
		cmd_export_add(base, cmd);
	exit_status(0, 0);
	return (0);
}
