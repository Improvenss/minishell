/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:46:00 by gsever            #+#    #+#             */
/*   Updated: 2022/10/26 16:13:13 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*cmd_node_create(t_cmd **new, t_lexer *last, int i, int l)
{
	t_lexer *tmp;

	tmp = last;
	*new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!*new)
		return (NULL);
	(*new)->full_cmd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*new)->full_cmd)
		return (NULL);
	(*new)->redirect = (char **)malloc(sizeof(char *) * (l + 1)); //+1
	if (!(*new)->redirect) //+1
		return (NULL); //+1
	(*new)->infile = STDIN_FILENO;
	(*new)->outfile = STDOUT_FILENO;
	(*new)->next = NULL;
	tmp = last;
	i = 0;
	l = 0; //+1
	while (tmp && tmp->flag != TOK_PIPE)
	{
		if (tmp->flag & (TOK_TEXT | TOK_D_QUOTE | TOK_S_QUOTE))//if (tmp->flag == TOK_TEXT)
		{
			if (tmp->str[0] != '\0')// cat $pwd icin
			{
				(*new)->full_cmd[i] = ft_strdup(tmp->str);
				i++;
			}
		}
		else if (tmp->flag & (TOK_REDIR | TOK_HEREDOC | TOK_REDIR_FILE)) // +1
		{
			if (tmp->str[0] != '\0') //cat $pwd için
			{
				(*new)->redirect[l] = ft_strdup(tmp->str);
				l++;
			}
		}
		// if (tmp->str[0] != '\0')
		// 	cmd_set_fd(tmp, new);
		tmp = tmp->next;
	}
	(*new)->full_cmd[i] = NULL;
	(*new)->redirect[l] = NULL; //+1
	(*new)->size = i;
	(*new)->red_size = l; //+1
	return (tmp);
}

t_lexer	*cmd_create(t_cmd **lst, t_lexer *last)
{
	t_lexer *tmp;
	t_cmd	*new;
	int		i;
	int		l; // +1

	new = NULL;
	tmp = last;
	i = 0;
	l = 0; // +1
	while (tmp && tmp->flag != TOK_PIPE)
	{
		if (tmp->flag & (TOK_TEXT | TOK_D_QUOTE | TOK_S_QUOTE))
			i++;
		else
			l++;
		tmp = tmp->next;
	}
	tmp = cmd_node_create(&new, last, i, l); // +1
	cmd_lstadd_back(lst, new);
	if (tmp && tmp->flag == TOK_PIPE)
		tmp = tmp->next;
	return (tmp);
}

t_cmd	*cmd_lstlast(t_cmd *cmd)
{
	t_cmd *tmp;

	if (cmd == NULL)
		return (NULL);
	tmp = cmd;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	cmd_set_me_fd(t_cmd *cmd, int max)
{
	int	i;
	int	last_in;
	int	last_out;
	int flags[2];

	i = -1;
	last_in = -1;
	last_out = -1;
	//printf("%d\n", __LINE__);
	while (cmd->redirect[++i])
	{
		if (ft_strncmp_edited(cmd->redirect[i], "<<", 2))
		{
			cmd->infile = set_heredoc(cmd->redirect[i + 1]);
			if (cmd->redirect[i + 1] == NULL)
				last_in = cmd->infile; // son argüman ise hafızaya almam gerekiyor. Değilse zaten bir işe yaramayacak.
			if (cmd->infile == -1)
				return (0);
		}
	}
	i = max - 2;
	//printf("%d\n", __LINE__);
	while (i >= 0 && exit_status(0, 1) == 0)
	{
		if (ft_strncmp_edited(cmd->redirect[i], ">>", 2))
		{
			flags[0] = 1;
			flags[1] = 1;
			// if (cmd->outfile != 1)
			// 	close(cmd->outfile);
			cmd->outfile = set_fd(cmd->outfile, cmd->redirect[i + 1], flags);
			if (i == max - 2)
				last_out = cmd->outfile;

		}
		else if (ft_strncmp_edited(cmd->redirect[i], ">", 1))
		{
			flags[0] = 1;
			flags[1] = 0;
			// if (cmd->outfile != 1)
			// 	close(cmd->outfile);
			cmd->outfile = set_fd(cmd->outfile, cmd->redirect[i + 1], flags);
			if (i == max - 2)
				last_out = cmd->outfile;
		}
		else if (ft_strncmp_edited(cmd->redirect[i], "<", 1))
		{
			flags[0] = 0;
			flags[1] = 0;
			// if (cmd->infile != 0)
			// 	close(cmd->infile);
			cmd->infile = set_fd(cmd->infile, cmd->redirect[i + 1], flags);
			if (i == max - 2)
				last_in = cmd->infile;
		}
		i--;
	}
	if (last_in != -1)
		cmd->infile = last_in;
	if (last_out != -1)
		cmd->outfile = last_out;
	if (cmd->outfile == -1 || cmd->infile == -1)
		exit_status(1, 0);
	return (1);
}

void	cmd_set_me(t_base *base)
{
	t_cmd	*tmp;
	int		i;

	i = base->cmd_count;
	tmp = cmd_lstlast(base->cmd); // cmd'nin en son argümanından başlamam gerekiyor.
	while (i-- > 0 && tmp)
	{
		if (tmp->red_size > 0)
			cmd_set_me_fd(tmp, tmp->red_size);
		tmp = tmp->prev;
	}
}

void	cmd(t_base *base)
{
	t_lexer	*tmp;

	tmp = base->lexer;
	while (tmp)
	{
		tmp = cmd_create(&base->cmd, tmp);
	}
	base->cmd_count = cmd_count(base->cmd);
	exit_status(0, 0); // +1
	cmd_set_me(base); // +1
	debug_print_cmd(base, "DEBUG", "print");
	if (fork_init(base) == 0)
	{
		print_error(SHELLNAME, "fork", NULL, "Cannot allocate memory");
		cmd_exit(base, base->cmd);
	}
	if (exit_status(0, 1) == 0) // +1
		fork_start(base);
	else
		exit_status(1, 0);
}
