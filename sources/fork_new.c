/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:26:28 by gsever            #+#    #+#             */
/*   Updated: 2022/10/03 17:17:50 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_wait(t_base *base)
{
	int	i;

	i = -1;
	while (++i < base->split_count)
		waitpid(base->pid[i], &base->status, 0);
}

void	fd_close(t_base *base)
{
	int	i;

	i = -1;
	while (++i < base->split_count)
	{
		close(base->fd[i][0]);
		close(base->fd[i][1]);
	}
}

void	fork_dup(t_base *base, int i)
{
	if (i > 0)
		dup2(base->fd[i - 1][0], 0);
	if (i != base->split_count - 1)
		dup2(base->fd[i][1], 1);
}

int	fork_start(t_base *base, int i)
{
	while (++i < base->split_count && base->split_count > 1)
	{
		base->pid[i] = fork();
		if (base->pid[i] == 0)
		{
			fork_dup(base, i);
			fd_close(base);
			if (command_exec(base, base->pipe_line[i]) == ERROR)
				print_error(SHELL_NAME, NULL, NULL,
				"command_exec not working!\n");
			exit(0);
		}
	}
	if (base->split_count > 1)
	{
		fd_close(base);
		ft_wait(base);
	}
	if (base->split_count == 1)
		command_exec(base, base->pipe_line[i]);
	return (0);
}

/**
 * @brief pipe'nin forkunu initliyoruz. En az 1 pipe varsa gerceklesiyor.
 * 
 * base->split_count -> pipe sayisi olmus oluyor.
 * @note malloc icin ayrilan * 2'lik yer stdout ve stdin'i temsil etmektedir.
 * 
 * @param base 
 */
int	fork_init(t_base *base)
{
	int	i;

	if (base->split_count > 1)
	{
		base->fd = (int **)malloc(sizeof(int *) * (base->split_count + 1));
		if (base->fd == NULL)
			return (0);
		i = -1;
		while (++i < base->split_count)
		{
			base->fd[i] = (int *)malloc(sizeof(int) * 2);
			if (base->fd[i] == NULL)
				return (0);
			pipe(base->fd[i]);
		}
		base->pid = (int *)malloc(sizeof(int) * base->split_count);
		if (base->pid == NULL)
			return (0);
	}
	return (1);
}
