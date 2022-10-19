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

int	set_arg(t_base *base, char **environ)
{
	int	i;

	base->cmd = NULL;
	base->env = NULL;
	base->lexer = NULL;
	i = -1;
	while (environ[++i])
	{
		if (env_struct(base, environ[i]) == ERROR)
		{
			env_free(&base->env);
			exit_status(ENOMEM, 0);
			return (print_error(SHELLNAME, "env", NULL, strerror(ENOMEM)));
		}
	}
	base->env_path = ft_split(env_findret(base, "PATH"), ':');
	if (base->env_path == NULL)
	{
		exit_status(ENOMEM, 0);
		return (print_error(T_NAME, "env_path", NULL, strerror(ENOMEM)));
	}
	return (0);
}

int	main(int argc __attribute((unused))
	, char **argv __attribute((unused))
	, char **envp)
{
	t_base	base;

	if (set_arg(&base, envp) != ERROR)
		minishell(&base);
	return (exit_status(0, 1));
}
