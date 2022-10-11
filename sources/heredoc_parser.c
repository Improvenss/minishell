/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:14:13 by gsever            #+#    #+#             */
/*   Updated: 2022/10/10 15:12:37 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	heredoc_merge(t_lexer *redir_file, t_lexer **lexer __attribute((unused)))
{
	t_lexer	*iter;
	t_lexer	*tmp;

	if (redir_file->flag & TOK_CONNECTED)
	{
		redir_file->flag &= ~(TOK_CONNECTED);
		iter = redir_file->next;
		while (iter && iter->flag & TOK_CONNECTED)
		{
			if (iter->flag & TOK_S_QUOTE)
				redir_file->flag |= TOK_S_QUOTE;
			if (iter->flag & TOK_D_QUOTE)
				redir_file->flag |= TOK_D_QUOTE;
			tmp = iter->next;
			// lst_node_remove(lexer, iter, c_token_destroy);
			iter = tmp;
		}
		if (iter->flag & TOK_S_QUOTE)
			redir_file->flag |= TOK_S_QUOTE;
		if (iter->flag & TOK_D_QUOTE)
			redir_file->flag |= TOK_D_QUOTE;
		// lst_node_remove(lexer, iter, c_token_destroy);
	}
}

static char	*heredoc_readline(char *limiter)
{
	char	*read_str;
	char	*here_str;

	signal(SIGINT, signal_ctrl_heredoc);
	here_str = ft_strdup("");
	if (here_str == NULL)
		return (NULL);
	read_str = readline("> ");
	while (read_str && ft_strncmp(read_str, limiter, ft_strlen(limiter) + 1))
	{
		read_str = str_append_chr(read_str, '\n');
		if (read_str == NULL)
		{
			free(here_str);
			print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM));
			return (NULL);
		}
		here_str = str_append_str(here_str, read_str);
		if (here_str == NULL)
			break ;
		free(read_str);
		read_str = readline("> ");
	}
	free(read_str);
	return (here_str);
}

static int	heredoc_processing(t_lexer *redir_file, char **limiter)
{
	int	fd;

	fd = dup(STDIN_FILENO);
	if (fd == -1)
		return (print_error_errno(SHELLNAME, NULL, NULL));
	free(redir_file->str);
	redir_file->str = heredoc_readline(*limiter);
	if (errno == EBADF)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			print_error_errno(SHELLNAME, NULL, NULL);
		close(fd);
		return (ERROR);
	}
	close(fd);
	if (redir_file->str == NULL)
		return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
	return (0);
}

int	parser_heredoc(t_lexer *lexer)
{
	t_lexer	*redir_file;
	char	*limiter;

	if (lexer && redir_type(lexer->str) == REDIR_HEREDOC)
	{
		redir_file = lexer->next;
		limiter = token_to_str(redir_file);
		if (limiter == NULL)
			return (print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM)));
		if (heredoc_processing(redir_file, &limiter) == ERROR)
		{
			free(limiter);
			return (ERROR);
		}
		free(limiter);
		redir_file->flag |= TOK_HEREDOC;
		heredoc_merge(redir_file, &lexer);
	}
	return (0);
}
