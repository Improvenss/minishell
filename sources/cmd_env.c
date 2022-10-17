/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:15:41 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/15 21:15:41 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_env(t_base *base, t_cmd *cmd)
{
	t_env	*tmp;
	int		i;

	ft_putendl_fd(GREEN"cmd_env() calisti"END, 1);
	tmp = base->env;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->data[1] != NULL)
		{
			while (tmp->data[0][i])
				write(cmd->outfile, &tmp->data[0][i++], 1);
			write(cmd->outfile, "=", 1);
			i = 0;
			while (tmp->data[1][i])
				write(cmd->outfile, &tmp->data[1][i++], 1);
			write(cmd->outfile, "\n", 1);
		}
		else if (tmp->is_env_equal && tmp->data[1] == NULL)
		{
			while (tmp->data[0][i])
				write(cmd->outfile, &tmp->data[0][i++], 1);
			write(cmd->outfile, "=\n", 2);
		}
		tmp = tmp->next;
	}
	g_status = 0;
	return (0);
}
