/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:19:14 by gsever            #+#    #+#             */
/*   Updated: 2022/09/28 17:11:01 by akaraca          ###   ########.fr       */
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
 * @brief exter char **env yapısı, struct yapısına atandığından,
 * 		yapı içerisindeki verileri çekebilmek için bu fonk. kullanılmaktadır.
 * 
 * @param env_name "OLDPWD=", "PWD=", "HOME="... gibi 
 * 		string yapıları ile belirtilmelidir.
 * @param base 
 * @return char* Gönderilen string yok ise NULL, var ise ='den sonraki
 * 		stringin index'inin adresi döndürülmektedir.
 */
char	*env_findret(char *env_name, t_base *base)
{
	int	i;
	int	l;
	int	count;

	i = 0;
	while (base->environ[i])
	{
		l = 0;
		count = 0;
		while (base->environ[i][l])
		{
			if (base->environ[i][count] == env_name[count])
				count++;
			if (env_name[count] == '\0')
				return (&base->environ[i][count]);
			l++;
		}
		i++;
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
	while (str[i] == 32 && str[i])
		i++;
	while (str[l] == 32 && str[l])
		l--;
	tmp = (char *)malloc(sizeof(char) * (l - i));
	if (!tmp)
		return (NULL);
	while (str[i] && i <= l)
	{
		while (str[i - 1] == 32 && str[i] == 32)
			i++;
		tmp[k] = str[i];
		k++;
		i++;
	}
	tmp[k] = '\0';
	free(str);
	return (tmp);
}
