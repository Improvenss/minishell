/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:10:01 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/15 15:10:01 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static const struct s_commands	g_commands[] = {
	{"echo", cmd_echo},
	{"cd", cmd_cd},
	{"pwd", cmd_pwd},
	{"unset", cmd_unset},
	{"export", cmd_export},
	{"env", cmd_env},
	{"exit", cmd_exit},
	{NULL, NULL},
};

char	*ft_path(char **path, char *cmd_name)
{
	char *dir1;
	char *dir2;
	int i = -1;
	while (path[++i])
	{
		dir2 = ft_strjoin("/", cmd_name);
		dir1 = ft_strjoin(path[i], dir2);
		free(dir2);
		if (access(dir1, 0) == 0)
		{
			return (dir1);
		}
		free(dir1);
	}
	return (NULL);
}

int	file_or_dir_search(char *str, int flag)
{
	int	fd;

	fd = open(str, flag); //NO_MATCH (0)-> Flag olarak bir tanımlıyıcıya ihtiyacımız yok, belirtilen dizin içerisinde dosya varlık yokluk kontrolü gereklidir. (windowsta var)
	close(fd);
	if (fd == -1) //dosya yok ise -1 döner.
		return (0);
	return (1);
}

int	search_and_launch(char **cmd_array)
{
	if (ft_strncmp(cmd_array[0], "./", 2))
		return (0);
	if (!file_or_dir_search(cmd_array[0], 0))
		return (0);
	return (1);
}

int	cmd_other(t_base *base, char **cmd_array)
{
	if (search_and_launch(cmd_array))
	{
		if (file_or_dir_search(cmd_array[0], O_DIRECTORY))
		{
			print_error(SHELLNAME, NULL, cmd_array[0], "Is a directory");
			g_status = 1;
		}
		else
		{
			extern char **environ; /////////kaldırılcak, base->env char** yapısında olmadığından hatalı durumda.
			int pi;
			pi = fork();
			if (pi == 0)
				g_status = execve(ft_path(base->PATH, cmd_array[0]), cmd_array, environ);
			waitpid(pi, &g_status, 0);
		}
	}
	else if (ft_path(base->PATH, cmd_array[0]))
	{
		extern char **environ; /////////kaldırılcak, base->env char** yapısında olmadığından hatalı durumda.
		int pi;
		pi = fork();
		if (pi == 0)
		{
			if (base->fd_i != base->cmd_count - 1)
			{
				dup2(base->cmd->infile, 0);
				dup2(base->cmd->outfile, 1);
			}
			g_status = execve(ft_path(base->PATH, cmd_array[0]), cmd_array, environ);
		}
		waitpid(pi, &g_status, 0);
	}
	else
	{
		print_error(SHELLNAME, NULL, cmd_array[0], "command not found");
		g_status = 127;
	}
	return (0);
}

int	command_find_arr(t_base *base, char **cmd_array)
{
	int	c_name;
	int	i;

	if (cmd_array[0] == NULL)
		return (0);
	i = -1;
	while (cmd_array && g_commands[++i].name != NULL)
	{
		c_name = ft_strlen(g_commands[i].name);
		if (cmd_array && ft_strncmp_edited(cmd_array[0],
			g_commands[i].name, c_name))
		{
			return (i + 1);
		}
	}
	return (cmd_other(base, cmd_array));
}

int	command_exec(t_base *base, t_cmd *cmd)
{
	int	cmd_i;

	cmd_i = command_find_arr(base, cmd->full_cmd);
	if (cmd_i == 127)
		return (ERROR);
	if (cmd_i > 0 && cmd_i < 8)
		return (g_commands[cmd_i - 1].func(base, cmd));
	return (0);
}
