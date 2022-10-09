/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 23:53:38 by gsever            #+#    #+#             */
/*   Updated: 2022/10/09 17:38:54 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief base->cmds[].name && base->cmds[].func initializing.
 * 
 * @param base base->cmds[] icin.
 */
void	cmd_init(t_base *base)
{
	base->cmds[0] = (t_cmds){"echo", cmd_echo};
	base->cmds[1] = (t_cmds){"cd", cmd_cd};
	// base->cmds[2] = (t_cmds){"pwd", cmd_pwd};
	// base->cmds[3] = (t_cmds){"unset", cmd_unset};
	// base->cmds[4] = (t_cmds){"export", cmd_export};
	// base->cmds[5] = (t_cmds){"env", cmd_env};
	// base->cmds[6] = (t_cmds){"exit", cmd_exit};
	base->cmds[2] = (t_cmds){NULL, NULL};
}

// int	cmd_other(t_base *base, char *pipe_line)
// {
// 	int pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		execve(ft_path(base->PATH, pipe_line),
// 			ft_split(pipe_line, ' '), base->environ);
// 	}
// 	waitpid(pid, &base->status, 0);
// 	return (0);
// }

int	command_find(t_base *base)
{
	// int	c_name;
	// int	i;
	(void)base;

	// i = -1;
	// while (base->parser->type == )
	return (0);
}

int	command_exec(t_base *base)
{
	int	cmd_i;

	cmd_i = command_find(base);
	if (cmd_i == 127)
		return (ERROR);
	return (base->cmds[cmd_i - 1].func(base));
}

// int	command_find_arr(t_base *base)
// 	int	c_name;
// 	int	i;

// 	// base->array_line = array_split(pipe_line);
// 	i = -1;
// 	while (base->lexer->str != NULL && base->cmds[++i].name != NULL)
// 	{
// 		c_name = ft_strlen(base->cmds[i].name);
// 		printf("base->cmds[i].name -> %s\n", base->cmds[i].name);
// 		if (base->lexer && ft_strncmp_edited(base->lexer[i].str,
// 			base->cmds[i].name, c_name))
// 		{
// 			printf("base->cmds[%d]\n", i);
// 			return (i + 1);
// 		}
// 	}
// 	// return (cmd_other(base, pipe_line));
// 	return (printf("cmd_other_calisacak\n"));
// }

// int	command_exec(t_base *base)
// {
// 	int	cmd_i;

// 	cmd_i = command_find_arr(base);
// 	printf("command_exex -> cmd_i -> %d\n", cmd_i);
// 	if (cmd_i == 127)
// 		return (ERROR);
// 	if (cmd_i <= 0) //düzenle. mADGE
// 		return (0);
// 	return (base->cmds[cmd_i - 1].func(base));
// }
