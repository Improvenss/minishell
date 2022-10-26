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

/**
 * @file command.c
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

/**
 * @brief PDF'den istenilen komutlarimizi burada base->commands[]'i
 *  t_commands structuna init ediyoruz.
 * 
 * Terminal'imize girilen girdimizde buradaki komutlardan biri varsa sahip
 *  olduklari functionlari calistirilacak.
 * 
 * @param base base->commands[8]'in icine init ediyoruz.
 * @fn cmd_echo()
 * @fn cmd_cd()
 * @fn cmd_pwd()
 * @fn cmd_unset()
 * @fn cmd_export()
 * @fn cmd_env()
 * @fn cmd_exit()
 */
void	commands_init(t_base *base)
{
	base->commands[0] = (t_commands){"echo", cmd_echo};
	base->commands[1] = (t_commands){"cd", cmd_cd};
	base->commands[2] = (t_commands){"pwd", cmd_pwd};
	base->commands[3] = (t_commands){"unset", cmd_unset};
	base->commands[4] = (t_commands){"export", cmd_export};
	base->commands[5] = (t_commands){"env", cmd_env};
	base->commands[6] = (t_commands){"exit", cmd_exit};
	base->commands[7] = (t_commands){NULL, NULL};
}

void action_execve(int sig)
{
	if (sig == SIGINT)
	{
		exit_status(1, 0);
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		//rl_on_new_line();
	}
}

void	cmd_execve(t_base *base, t_cmd *cmd, char *command, char **cmd_array)
{
	int	pi;

	pi = fork();
	if (pi == 0)
	{
		if (base->fd_i != base->cmd_count - 1)
		{
			dup2(cmd->infile, 0);
			dup2(cmd->outfile, 1);
		}
		if (cmd->infile == -1 || cmd->outfile == -1)
			exit(1);
		else
			base->err = execve(command, cmd_array, base->env_chr);
	}
	waitpid(pi, &base->err, 0);
	if (-1 & (cmd->infile | cmd->outfile)) // execve err çıktısını 256'ya böldüğünden dolayı ayrı bir exit durumu söz konusu ise 256'ya bölünmelidir.
		base->err = base->err / 256;
	exit_status(base->err, 0);
}

int	cmd_other(t_base *base, t_cmd *cmd, char **cmd_array)
{
	base->mem_1 = ft_path(base->env_path, cmd_array[0]);
	base->env_chr = env_be_char(base->env);
	signal(SIGINT, action_execve); // pipe dışında kullanıldığında wc'yi düzeltiyor.
	if (search_and_launch(cmd_array))
	{
		if (file_or_dir_search(cmd_array[0], O_DIRECTORY))
		{
			print_error(SHELLNAME, NULL, cmd_array[0], "Is a directory");
			exit_status(1, 0);
		}
		else
			cmd_execve(base, cmd, base->mem_1, cmd_array);
	}
	else if (base->mem_1 && !file_or_dir_search(cmd_array[0], O_DIRECTORY)) // . ve .. yazınca çalışıyordu bu yüzden directory değilse durumu berlirttik.
		cmd_execve(base, cmd, base->mem_1, cmd_array); // grep'in çalışması için lazım.
	else if (access(cmd_array[0], 0) == 0 && !file_or_dir_search(cmd_array[0], O_DIRECTORY)) //$HOME dizini access'de 0 değerini alıyor ama bu bir dizi, bu yüzden buraya girmemelidir.
		cmd_execve(base, cmd, cmd_array[0], cmd_array); // /bin/ls için
	else 
	{
		print_error(SHELLNAME, NULL, cmd_array[0], "command not found");
		exit_status(127, 0);
	}
	free(base->mem_1);
	free_pp_str(base->env_chr);
	return (0);
}

/**
 * @brief base->commands[]'in icinde isimleriyle cmd_array'ini
 *  karsilastiriyoruz.
 * 
 * NULL: return (0).
 * FIND: cmd_*.c icindeki gerekli komutun index sirasini donduruyor
 *  o yuzden i + 1 var.
 * NFIND: cmd_other()'e giderek execve()'yle cmd_array'i calistiriyor.
 * 
 * @param base 
 * @param cmd_array 
 * @fn ft_strlen(): command_name; base->commands[0]'daki 
 * NOTE: exit komutu yazildiginda exit'e ozel olarak ERROR donecek
 * @return int NULL: 0, OK: commands[] index'i, NOK: execve's return value.
 */
int	command_find_arr(t_base *base, t_cmd *cmd, char **cmd_array)
{
	int	c_name;
	int	i;

	if (cmd_array[0] == NULL)
		return (0);
	i = -1;
	while (cmd_array && base->commands[++i].name != NULL)
	{
		c_name = ft_strlen(base->commands[i].name);
		if (cmd_array && ft_strncmp_edited(cmd_array[0],
			base->commands[i].name, c_name))
		{
			return (i + 1);
		}
	}
	return (cmd_other(base, cmd, cmd_array));
}

/**
 * @brief Genel komut calistirma islemi buradan basliyor.
 * 
 * 			lexer->parser->expander
 * FIND: Islemleri bittikten sonra bizim kendi tanimladigimiz base->commands[]
 *  structunun icinde base->cmd->full_cmd komutlarimizi ariyoruz,
 *  buldugumuzda kendi yazmis oldugumuz cmd_* func()'larimizi calistiriyoruz.
 * NFIND: Eger bulamazsak return(0);
 * 
 * @param base 
 * @param cmd 
 * @return int 
 */
int	command_exec(t_base *base, t_cmd *cmd)
{
	int	cmd_i;

	cmd_i = command_find_arr(base, cmd, cmd->full_cmd);
	if (cmd_i > 0 && cmd_i < 8)
		return (base->commands[cmd_i - 1].func(base, cmd));
	return (0);
}
