/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:42:56 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/13 08:42:56 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_error(char *s1, char *s2, char *s3, char *message)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
	{
		if (s1)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s2, 2);
	}
	if (s3)
	{
		if (s1 || s2)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s3, 2);
	}
	if (message)
	{
		if (s1 || s2 || s3)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	ft_putchar_fd('\n', 2);
	return (ERROR);
}

int	set_arg(t_base *base, char **environ)
{
	int	i;

	g_status = 0;
	base->cmd = NULL;
	base->env = NULL;
	base->lexer = NULL;
	i = -1;
	while (environ[++i])
		env_struct(base, environ[i]);
	base->PATH = ft_split(env_findret(base, "PATH"), ':');
	if (base->PATH == NULL)
		return (print_error(T_NAME, NULL, NULL, strerror(ENOMEM)));
	return (0);
}

int	main(int argc __attribute((unused))
	, char **argv __attribute((unused))
	, char **envp)
{
	t_base	base;

	if (set_arg(&base, envp) == ERROR)
		exit(EXIT_FAILURE);
	minishell(&base);
	return (0);
}
