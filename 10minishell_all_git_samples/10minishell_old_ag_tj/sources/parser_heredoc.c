/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:46:20 by gsever            #+#    #+#             */
/*   Updated: 2022/10/06 13:49:28 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser_heredoc(t_list *l_token)
{
	t_list	*redir_file;
	char	*limiter;

	if (l_token && redir_type(token_content(l_token)->str) == REDIR_HEREDOC)
	{
		redir_file = l_token->next;
		limiter = token_to_str(redir_file);
		if (limiter == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		if (heredoc_processing(redir_file, &limiter) == ERROR)
		{
			free(limiter);
			return (ERROR);
		}
		free(limiter);
		token_content(redir_file)->flags |= TOK_HEREDOC;
		heredoc_merge(redir_file, &l_token);
	}
	return (0);
}