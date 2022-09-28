/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:47:36 by akaraca           #+#    #+#             */
/*   Updated: 2022/09/28 15:18:15 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 * @fn access() Dosya var mi yok mu bakiyor kontrol ediyor,
 * 	varsa 0 yoksa -1 donduruyor.
 * @param base 
 */
void	ft_fork(t_base *base)
{
	int	l;
	int	i;
	int err;

	l = 0;
	while (l < base->split_count)
	{
		base->pid[l] = fork();
		if (base->pid[l] != 0 && base->array_line[l]) // base->array_line[l], enter girdisi sonrasında hata döndürdüğünden dolayı koşul eklendi.
		{
			err = access(ft_path(base->PATH, base->array_line[l]), 0);
			if (err == -1)
				printf("FORK: Error\n");
		}
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

void	ft_fd(t_base *base)
{
	int l;

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
}