/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:35:34 by gsever            #+#    #+#             */
/*   Updated: 2022/10/01 22:10:34 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file command.c
 * @author Gorkem SEVER (gsever)
 * @author Ahmet KARACA (akaraca)
 * 
 * @brief Komutlari bulup uyguladigimiz yer.
 * 
 * @version 0.1
 * @date 2022-09-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../includes/minishell.h"

/**
 * @brief 
 * http://unixwiz.net/techtips/gnu-c-attributes.html
 */
static const struct s_commands	g_commands[] = {
	{"echo", cmd_echo},
	{"cd", cmd_cd},
	{NULL, NULL},
};
	// {"pwd", cmd_pwd},
	// {"env", cmd_env},
	// {"export", cmd_export},
	// {"unset", cmd_unset},

int	command_find_arr(t_base *base, char *pipe_line)
{
	int	c_name;
	int	i;

	base->array_line = array_split(pipe_line);
	i = -1;
	while (base->array_line && g_commands[++i].name != NULL)
	{
		c_name = ft_strlen(g_commands[i].name);
		// if (base->array_line && !ft_strncmp(base->array_line, "exit", 5))
		// 	return (INT_MAX);
		printf("g_commands[i].name -> %s\n", g_commands[i].name);
		if (base->array_line && !ft_strncmp(base->array_line[i],
			g_commands[i].name, c_name + 1))
		{
			printf("g_commands[%d]\n", i);
			return (i + 1);
		}
	}
	return (0);
}

int	command_exec(t_base *base, char *pipe_line)
{
	int	cmd_i;

	cmd_i = command_find_arr(base, pipe_line);
	printf("cmd_i -> %d\n", cmd_i);
	if (cmd_i == 0)
		return (ERROR);
	// else if (cmd_i == INT_MAX)
	// 	return (ft_putendl_fd("exit", STDERR_FILENO));
	return (g_commands[cmd_i - 1].func(base));
}

void	command_find(t_base *base, char *pipe_line)
{
	printf("%s\n", pipe_line);
	base->array_line = array_split(pipe_line);
	/*int i = 0;
	while (base->array_line[i])
	{
		printf("%s\n", base->array_line[i++]);
	}*/
	if (base->array_line[0] == NULL)
		printf("%c",'\0');
	else if (ft_strncmp_edited(base->array_line[0], "echo", 4))
		cmd_echo(base);
	else
	{
		int pi = fork();
		if (pi == 0)
		{
			execve(ft_path(base->PATH, base->array_line[0]), base->array_line, base->environ);
		}
		waitpid(pi, 0, 0);
	}
	ft_free(base->array_line);
	exit(0);
}
