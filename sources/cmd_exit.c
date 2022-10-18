/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:23:33 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/15 15:23:33 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	err_num_is_num(char *argv)
{
	int	i;

	if (argv[0] == '\0')
	{
		print_error(SHELLNAME, "exit", argv, "numeric argument required");
		return (false);
	}
	i = -1;
	while (argv[++i])
	{
		if (!ft_isdigit(argv[i]))
		{
			print_error(SHELLNAME, "exit", argv, "numeric argument required");
			return (false);
		}
	}
	return (true);
}

int	cmd_exit(t_base __unused *base, t_cmd *cmd)
{
	int	argc;

	argc = 0;
	ft_putendl_fd(RED"exit"END, STDERR_FILENO);
	while (cmd->full_cmd[argc])
		argc++;
	if (argc >= 2 && err_num_is_num(cmd->full_cmd[1]) == false)
		errno = 255;
	else if (argc == 2)
		errno = ft_atoi(cmd->full_cmd[1]);
	else if (argc > 2)
	{
		print_error(SHELLNAME, "exit", NULL, "to many arguments");
		return (EXIT_FAILURE);
	}
	exit(errno);
}
