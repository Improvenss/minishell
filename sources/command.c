/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:35:34 by gsever            #+#    #+#             */
/*   Updated: 2022/10/03 19:56:43 by gsever           ###   ########.fr       */
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
	{"pwd", cmd_pwd},
	{"exit", cmd_exit},
	{NULL, NULL},
};
	//{"export", cmd_export},
	//{"unset", cmd_unset},
	//{"env", cmd_env},

int	command_find_arr(t_base *base, char *pipe_line)
{
	int	c_name;
	int	i;

	base->array_line = array_split(pipe_line);
	i = -1;
	while (base->array_line && g_commands[++i].name != NULL)
	{
		c_name = ft_strlen(g_commands[i].name);
		// printf("g_commands[i].name -> %s\n", g_commands[i].name);
		if (base->array_line && ft_strncmp_edited(base->array_line[0],
			g_commands[i].name, c_name))
		{
			// printf("g_commands[%d]\n", i);
			return (i + 1);
		}
	}
	return (cmd_other(base, pipe_line));
}

int	command_exec(t_base *base, char *pipe_line)
{
	int	cmd_i;

	cmd_i = command_find_arr(base, pipe_line);
	// printf("cmd_i -> %d\n", cmd_i);
	if (cmd_i == 127)
		return (ERROR);
	if (cmd_i <= 0) //düzenle. mADGE
		return (0);
	return (g_commands[cmd_i - 1].func(base));
}
