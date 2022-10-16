/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:47:06 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/13 08:47:06 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_free(t_cmd **cmd)
{
	t_cmd	*tmp;

	while (*cmd && (*cmd)->next != NULL)
	{
		tmp = (*cmd)->next;
		free(*cmd);
		(*cmd) = tmp;
	}
	*cmd = NULL;
}

void	lexer_free(t_lexer **lexer)
{
	t_lexer *tmp;

	while (*lexer && (*lexer)->next != NULL)
	{
		tmp = (*lexer)->next;
		//if ((*lexer)->str[0] != '\0')
		//	free((*lexer)->str);
		free(*lexer);
		(*lexer) = tmp;
	}
	*lexer = NULL;
}

void	action(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	ft_strcmp_edited(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	history_empty_check(char *input_line)
{
	static char	*last_entry;
	int			i;
	int			l;

	if (ft_strcmp_edited(input_line, last_entry) == 0)
		return (0);
	free(last_entry);
	last_entry = ft_strdup(input_line);
	l = 0;
	i = 0;
	while (input_line[i])
	{
		if (input_line[i] == ' ')
			l++;
		i++;
	}
	if (i == l)
		return (0);
	return (1);
}

void	minishell(t_base *base)
{
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, action);
		base->input_line = readline(T_NAME);
		if (!base->input_line)
		{
			ft_putendl_fd(RED"exit"END, STDERR_FILENO);
			rl_clear_history();
			exit(0);
		}
		if (history_empty_check(base->input_line))
			add_history(base->input_line);
		processes(base);
		lexer_free(&base->lexer);
		cmd_free(&base->cmd);
		free(base->input_line);
		// system("leaks minishell");
	}
	rl_clear_history();
	//ft_free(base);
	exit(g_status);
}
