/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:48:49 by gsever            #+#    #+#             */
/*   Updated: 2022/10/26 16:25:40 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 * @param base 
 */
void	ft_wait(t_base *base)
{
	int	i;
	int	err;

	i = -1;
	while (++i < base->cmd_count)
		waitpid(base->pid[i], &err, 0);
	exit_status(err, 0);
}

void	fd_close(t_base *base)
{
	int	i;

	i = -1;
	while (++i < base->cmd_count)
	{
		close(base->fd[i][0]);
		close(base->fd[i][1]);
	}
}

void	fork_dup(t_base *base, int i, t_cmd *cmd)
{
	//printf("cmd_in:%d --- cmd_out:%d\n", cmd->infile, cmd->outfile);
	if (i > 0 && cmd->infile == 0) // Baktığı yer
	{
		//printf("INFILE: i:%d,,, cmd:%d\n", i, cmd->infile);
		dup2(base->fd[i - 1][0], 0); // infile
	}
	if (i != (base->cmd_count - 1))// && cmd->outfile == 1) // Çıkarttığı yer
	{
		//printf("OUTFILE: i:%d,,,cmd:%d\n", i, cmd->outfile);
		dup2(base->fd[i][1], 1); // outfile
	}
	// dup2(cmd->infile, 0);
	// dup2(cmd->outfile, 1);
	//--------------------------------------------------------//
	// if (i > 0) // Baktığı yer
	// {
	// 	if (cmd->infile != 0)
	// 		dup2(cmd->infile, 0);
	// 	else
	// 		dup2(base->fd[i - 1][0], 0); // infile
	// }
	// if (i != base->cmd_count - 1) // Çıkarttığı yer
	// {
	// 	if (cmd->outfile != 1)
	// 		dup2(cmd->outfile, 1);
	// 	else
	// 		dup2(base->fd[i][1], 1); // outfile
	// }
	//--------------------------------------------------------//
	// if (i > 0)
	// 	dup2(base->fd[i - 1][cmd->infile], 0);
	// if (i != base->cmd_count - 1)
	// 	dup2(base->fd[i][cmd->outfile], 1);
}

/**
 * @brief command_exec() burada calisacak.
 * 
 * @note base->cmd_count: Pipe sayisi + 1 kadar. Bu kadar process acilacak.
 * 
 * @param base 
 * @fn fork(): Eger birden fazla pipe'miz varsa o kadar calistirilacak
 *  ve islemi bitince sonlandirilacak.
 * @fn fork_dup(): Bir onceki pipe'den(fork'tan) bilgiyi alabilmek icin.
 * @fn fd_close()
 * @fn command_exec(): Komut burada calistirilacak, eger cmd_*()'da tanimli
 *  bir komut yoksa execve()'ye gonderilip calistirilacak.
 * @fn print_error(): Eger komutumuz ve execve'miz calismazsa
 *  yazdirilacak error.
 * @fn exit()
 * @fn ft_wait()
 * @return int 
 */
int	fork_start(t_base *base)
{
	t_cmd	*tmp;
	int		i;

	i = -1;
	base->fd_i = -1;
	tmp = base->cmd;
	while (base->cmd_count > 1 && ++i < base->cmd_count && tmp)
	{
		base->fd_i = i;
		// printf("#%s#\n", tmp->full_cmd[0]);
		if (ft_strncmp_edited(tmp->full_cmd[0], "wc", 2) == 0) // pipe içinde wc kullanıldığında düzeltiyor
		{
			signal(SIGINT, SIG_IGN); //içerideki sinyali ignorluyoruz.
		}
		base->pid[i] = fork();
		if (base->pid[i] == 0)
		{
			fork_dup(base, i, tmp);
			fd_close(base);
			// command_exec(base, tmp);
			// printf("buldumm\n");
			exit(command_exec(base, tmp));
		}
		tmp = tmp->next;
	}
	if (base->cmd_count > 1)
	{
		fd_close(base);
		ft_wait(base);
	}
	if (base->cmd_count == 1)
		command_exec(base, base->cmd);
	return (0);
}

int	fork_init(t_base *base)
{
	int	i;

	if (base->cmd_count > 1)
	{
		base->fd = (int **)malloc(sizeof(int *) * (base->cmd_count + 1));
		if (base->fd == NULL)
			return (0);
		i = -1;
		while (++i < base->cmd_count)
		{
			base->fd[i] = (int *)malloc(sizeof(int) * 2);
			if (base->fd[i] == NULL)
				return (0);
			pipe(base->fd[i]);
		}
		base->pid = (int *)malloc(sizeof(int) * base->cmd_count);
		if (base->pid == NULL)
			return (0);
	}
	return (1);
}
