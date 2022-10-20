/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:49:16 by gsever            #+#    #+#             */
/*   Updated: 2022/10/20 12:55:12 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	chr_free(char **line)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

void	cmd_free(t_cmd **cmd)
{
	t_cmd	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		chr_free((*cmd)->full_cmd);
		free(*cmd);
		(*cmd) = tmp;
	}
	*cmd = NULL;
}

void	lexer_free(t_lexer **lexer)
{
	t_lexer	*tmp;

	while (*lexer)
	{
		tmp = (*lexer)->next;
		free((*lexer)->str);
		free(*lexer);
		(*lexer) = tmp;
	}
	*lexer = NULL;
}

void	env_free(t_env **env)
{
	t_env *tmp;

	tmp = (*env);
	while (tmp != NULL)
	{
		chr_free(tmp->data);
		tmp = tmp->next;
	}
}

void	all_free(t_base **base)
{
	ft_putendl_fd(RED"exit"END, STDERR_FILENO);
	rl_clear_history();
	lexer_free(&(**base).lexer);
	cmd_free(&(**base).cmd);
	env_free(&(**base).env);
	free((*base)->input_line);
}
