/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:12:54 by gsever            #+#    #+#             */
/*   Updated: 2022/09/19 17:48:33 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Directory ismini aliyor.
 * 
 * @param path 
 * @return char* 
 */
char	*directory_name(char *path)
{
	int		i;

	i = ft_strlen(path);
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
