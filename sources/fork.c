/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:47:36 by akaraca           #+#    #+#             */
/*   Updated: 2022/09/29 17:04:40 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief <, <<, >, >> , ||, &&, ", ', ( simgeleri görünce
 * 		string bölünecek.
 * 
 * (""a << $HOME"") -> 1 yapı
 * ""a << $HOME""	-> 5 yapı
 * a << b			-> 3 yapı
 * 'a < b'			-> 1 yapı
 * @param s 
 * @return size_t 
 */
size_t	array_word_count(char *s)
{
	size_t	count;
	int		i;
	int		l;
	int		k;

	count = 0;
	i = 0;
	while (s[i])
	{
		k = 0;
		{
			while (s[i] && s[i] != '<' && s[i] != '>' && s[i] != '|' && s[i] != '&' && s[i] != '"' && s[i] != '\'' && s[i] != '(' && s[i] != 32)
			{
				i++;
				k++;
			}
			while (s[i] == 32)
				i++;
		}
		if (k != 0)
			count++;
		l = 0;
		while (METAS[l])
		{
			if (s[i] == METAS[l])
			{
				count++;
				i++;
				if (s[i] == METAS[l])
					i++;
				break;
			}
			l++;
		}
		if (s[i] == '"')
		{
			if (s[i - 1] == 32 || s[i - 1] == '|' || s[i - 1] == '&' || s[i - 1] == '>' || s[i - 1] == '<')
				count++;
			i++;
			while (s[i] != '"')
				i++;
			i++;
		}
		if (s[i] == '\'')
		{
			if (s[i - 1] == 32 || s[i - 1] == '|' || s[i - 1] == '&' || s[i - 1] == '>' || s[i - 1] == '<')
				count++;
			i++;
			while (s[i] != '\'')
				i++;
			i++;
		}
		if (s[i] == '(')
		{
			k = 1;
			while (k > 0) // (a) -> 1 yapı, ((a)) -> 1 yapı olmalıdır bu yüzden eklendi.
			{
				while (s[i] && s[i] != ')')
				{
					if (s[i] == '(')
						k++;
					i++;
				}
				i++;
				k--;
			}
			count++;
		}
	}
	return (count);
}

char	*array_alloc(char *s)
{
	char	*new;
	int		i;
	int		l;
	printf("...%c\n", s[0]);
	i = 0;
	if ((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' && s[i + 1] == '>') || s[i] == '|' || s[i] == '&')
		i = 2;
	else if  (s[i] == '<' || s[i] == '>')
		i++;
	else if (s[i] == '"')
	{
		i++;
		while (s[i] != '"')
			i++;
		i++;
	}
	else if (s[i] == '\'')
	{
		i++;
		while (s[i] != '\'')
			i++;
		i++;
	}
	else if (s[i] == '(')
	{
		int k = 1;
		while (k > 0)
		{
			while (s[i] != ')')
			{
				if (s[i] == '(')
					k++;
				i++;
			}
			k--;
		}
		i++;
	}
	else
	{
		while (s[i] && s[i] != '<' && s[i] != '>' && s[i] != '|' && s[i] != '&' && s[i] != '(' && s[i] != 32)
			i++;
		if (s[i] == '"' && s[i] == '\'')
		{
			i++;
			while (s[i] != '"' && s[i] != '\'')
				i++;
		}
	}
	printf("-->> %d\n", i);
	new = (char *)malloc(sizeof(char) * (i + 1));
	l = i;
	i = 0;
	while (i < l)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**array_split(char *s)
{
	char	**new;
	int		wordc;
	int		l;
	int		i;

	wordc = array_word_count(s);
	printf("%d\n", wordc);
	new = (char **)malloc(sizeof(char *) * (wordc + 1));
	l = 0;
	i = 0;
	while (s[l])
	{
		if (s[l])
		{
			new[i] = array_alloc(&s[l]);
			printf("                #%s#\n", new[i]);
			i++;
		}
		if (s[l] == '<')
		{
			while (s[l] == '<')
				l++;
		}
		else if (s[l] == '>')
		{
			while(s[l] == '>')
				l++;
		}
		else if (s[l] == '|' || s[l] == '&')
			l = l + 2;
		else if (s[l] == '"')
		{
			l++;
			while (s[l] != '"')
				l++;
			l++;
		}
		else if (s[l] == '\'')
		{
			l++;
			while (s[l] != '\'')
				l++;
			l++;
		}
		else if (s[l] == '(')
		{
			int k = 1;
			while (k > 0)
			{
				while (s[l] != ')')
				{
					if (s[l] == '(')
						k++;
					l++;
				}
				k--;
			}
			l++;
		}
		else
		{
			while (s[l] && s[l] != '<' && s[l] != '>' && s[l] != '|' && s[l] != '&' && s[l] != '(' && s[l] != 32)
				l++;
		}
		while (s[l] == 32)
			l++;
		/*while (s[l] && s[l] != '<' && s[l] != '>' && s[l] != '|' && s[l] != '&' && s[l] != '"' && s[l] != '\'' && s[l] != '(' && s[l] != 32)
			l++;
		while (s[l] && (s[l] == '<' || s[l] == '>' || s[l] == '|' || s[l] == '&' || s[l] == 32))
			l++;
		int k = 1;
		if (s[l] == '(')
		{
			while (k > 0)
			{
				while (s[l] && s[l] != ')')
				{
					if (s[l] == '(')
						k++;
					l++;
				}
				k--;
			}
			l++;
		}
		if (s[l] == '"')
		{
			l++;
			while (s[l] != '"')
				l++;
			l++;
		}
		if (s[l] == '\'')
		{
			l++;
			while (s[l] != '\'')
				l++;
			l++;
		}*/
	}
	new[i] = NULL;
	return (new);
}

void	ft_command_find(t_base *base, char *pipe_line)
{
	base->array_line = array_split(pipe_line);
	
	//ft_free(base->array_line);
	exit(0);
}

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
		if (base->pid[l] != 0 && base->pipe_line[l]) // base->array_line[l], enter girdisi sonrasında hata döndürdüğünden dolayı koşul eklendi.
		{
			err = access(ft_path(base->PATH, base->pipe_line[l]), 0);
			if (err == -1)
				printf("%c", '\0');
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
			
			/*char *görkem = ft_path(base->PATH, base->pipe_line[l]);
				if (görkem != NULL)
					execve(ft_path(base->PATH, base->pipe_line[l]), ft_split(base->pipe_line[l], ' '), base->environ);
				else
					exit(0);*/
			ft_command_find(base, base->pipe_line[l]);
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
