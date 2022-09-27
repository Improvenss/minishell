/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:41:13 by gsever            #+#    #+#             */
/*   Updated: 2022/09/27 18:16:51 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_path(char **path, char *tmp)
{
	char **str = ft_split(tmp, ' '); //ls -la'nın ls kısmı lazım.
	char *dir1;
	char *dir2;
	int i = -1;
	while (path[++i])
	{
		dir2 = ft_strjoin("/", str[0]);
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

void	ft_fork(t_base *base)
{
	int	l;
	int	i;

	l = 0;
	while (l < base->split_count)
	{
		base->pid[l] = fork();
		if (base->pid[l] == 0)
		{
			// printf("%d. Fork\n", l);
			if (base->split_count == 1)
			{
				// printf("Tek\n");
				dup2(base->fd[l][0], 0); //Tek argüman için close fonk gerek yok(içeride ve dışarıda). //waitpid gerekli.
			}
			else if (l == 0 && base->split_count != 1)
			{
				// printf("Başlangıç l: %d\n", l);
				dup2(base->fd[l][1], 1);
			}
			else if (l + 1 != base->split_count)
			{
				// printf("Orta l: %d\n", l);
				dup2(base->fd[l - 1][0], 0);
				dup2(base->fd[l][1], 1);
			}
			else if (l + 1 == base->split_count)
			{
				// printf("Son l: %d\n", l);
				dup2(base->fd[l - 1][0], 0);
			}
			i = 0;
			while (i < base->split_count - 1) // -1 olmaz ise ekrana yazdırma işlemini yapacak olan son fork işlemini yapmadan kapanacaktır.
			{
				// printf("Close fd[%d]\n", i);
				close(base->fd[i][0]);
				close(base->fd[i][1]);
				i++;
			}
			char *görkem = ft_path(base->PATH, base->array_line[l]);
				if (görkem != NULL)
					execve(ft_path(base->PATH, base->array_line[l]), ft_split(base->array_line[l], ' '), base->environ);
				else
					exit(0);
		}
		l++;
	}

	i = 0;
	while (i < base->split_count - 1)
	{
		//printf("%d. fd\n", i);
		close(base->fd[i][0]);
		close(base->fd[i][1]);
		i++;
	}
	i = 0;
	while (i < base->split_count)
	{
		//printf("%d. pid\n", i);
		waitpid(base->pid[i], 0, 0);
		i++;
	}
}

void	command_run(t_base *base)
{
	int	l;

	base->split_count = 0;
	base->array_line = divider(base->input_line, base);
	base->fd = (int **)malloc(sizeof(int *) * base->split_count);
	if (base->split_count == 1)
	{
		//printf("Tekli fd girdisi\n");
		base->fd[0] = (int *)malloc(sizeof(int) * 2);
	}
	l = 0;
	while (l < base->split_count - 1)
	{
		//printf("-fd l: %d\n", l);
		base->fd[l++] = (int *)malloc(sizeof(int) * 2);
	}
	l = 0;
	while (l < base->split_count - 1) //tek komut çalışığı için pipe gerek yok.
	{
		//printf("-pipe l: %d-\n", l);
		pipe(base->fd[l++]);
	}
	base->pid = (int *)malloc(sizeof(int) * base->split_count);

	ft_fork(base);
}
