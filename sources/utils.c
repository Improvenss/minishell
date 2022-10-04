/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:19:14 by gsever            #+#    #+#             */
/*   Updated: 2022/10/04 13:43:33 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free(char **line)
{
	int	i;

	i = -1;
	while (line[++i])
		free(line[i]);
	free(line);
}

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

/**
 * @brief Tırnak içerisinde bulunan 
 * 	syntax hatalarının görmezden gelinilmesi gerekiyor.
 * 
 * @param str 
 * @param i 
 * @return int Tırnak içerisinde değilse(1), içerisindeyse(0)
 */
int	look_the_quote(char *str, int i)
{
	int		l;
	char	token;

	l = 0;
	token = '\0';
	while (str[l])
	{
		if (token == '\0' && (str[l] == '"' || str[l] == '\'' ))
		{
			token = str[l];
			l++;
		}
		if (str[l] == token && l < i)
				token = '\0';
		if (str[l] == token && l > i)
			return (0);
		l++;
	}
	return (1);
}

/**
 * @brief 
 * 
 * @param str 
 * @return char* 
 */
char	*delete_space(char *str, int i, int k, int l)
{
	char	*tmp;

	l = ft_strlen(str);
	while (str[i] == 32 && str[i] && look_the_quote(str, i))
		i++;
	while (str[l] == 32 && str[l] && look_the_quote(str, l))
		l--;
	tmp = (char *)malloc(sizeof(char) * (l - i));
	if (!tmp)
		return (NULL);
	while (str[i] && i <= l)
	{
		while (str[i - 1] == 32 && str[i] == 32 && look_the_quote(str, i))
			i++;
		tmp[k] = str[i];
		k++;
		i++;
	}
	tmp[k] = '\0';
	free(str);
	return (tmp);
}
