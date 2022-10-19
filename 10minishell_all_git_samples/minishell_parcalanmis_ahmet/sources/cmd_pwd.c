/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:00:26 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/15 21:00:26 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_pwd(t_base *base, t_cmd *cmd)
{
	char	*output;
	int		i;

	if (cmd->full_cmd[1] == NULL)
	{
		i = 0;
		output = env_findret(base, "PWD");
		while (output[i])
		{
			write(cmd->outfile, &output[i], 1);
			i++;
		}
		write(cmd->outfile, "\n", 1);
		if (output != NULL)
			exit_status(0, 0);
	}
	else
	{
		print_error(SHELLNAME, "pwd", NULL, "too many arguments");
		exit_status(1, 0);
	}
	return (0);
}
