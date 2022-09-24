/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:19:14 by gsever            #+#    #+#             */
/*   Updated: 2022/09/24 10:52:24 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



/**
 * @brief Tırnak içerisinde bulunan syntax hatalarının görmezden gelinilmesi gerekiyor.
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
	char *tmp;

	l = ft_strlen(str);
	while (str[i] <= 32 && str[i])
		i++;
	while (str[l] <= 32 && str[l])
		l--;
	tmp = (char *)malloc(sizeof(char) * (l - i));
	if (!tmp)
		return (NULL);
	while (str[i] && i <= l)
	{
		while (str[i - 1] <= 32 && str[i] <= 32)
			i++;
		tmp[k] = str[i];
		k++;
		i++;
	}
	tmp[k] = '\0';
	free(str);
	return (tmp);
}