/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:21:12 by gsever            #+#    #+#             */
/*   Updated: 2022/10/05 14:07:37 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Environlarimizi bildirmek icin kullaniyoruz.
 * 
 * @fn split_count()
 * @fn malloc()
 * @fn print_error()
 * @fn strerror()
 * @fn ft_strdup()
 * @fn ft_free_split()
 * @return int 
 */
int	env_init(void)
{
	extern char	**environ;
	int			i;

	i = split_count(environ);
	if (i == 0)
		return (0);
	g_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (g_env == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	i = -1;
	while (environ[++i])
	{
		g_env[i] = ft_strdup(environ[i]);
		if (g_env[i] == NULL)
		{
			ft_free_split(&g_env);
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		}
	}
	g_env[i] = NULL;
	return (0);
}
