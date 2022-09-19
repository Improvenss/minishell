/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:12:54 by gsever            #+#    #+#             */
/*   Updated: 2022/09/19 13:35:53 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Directory ismini aliyor.
 * 
 * @param path 
 * @return char* 
 */
char	*directory_name(char *path)
{
	int		i;
	int		l;

	i = ft_strlen(path);
	l = i;
	if (i == 1)
		return ("/");
	while (path[i] != '/')
		i--;
	return (&path[++i]);
}

/**
 * @brief Terminal ismini ekrana basan func().
 * 
 * @return char* 
 */
char	*terminal_print(void)
{
	char	*name;
	char	*tmp;

	name = directory_name(env_findret("PWD"));
	tmp = ft_strjoin(GREEN"➟ ", name);
	name = ft_strjoin(tmp, " $ "END);
	free(tmp);
	return (name);
}
