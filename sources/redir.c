/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:08:50 by gsever            #+#    #+#             */
/*   Updated: 2022/10/10 18:02:30 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	argv_lstadd(t_argv **argv, t_lexer *new)
{
	// t_argv	*tmp;

	printf("%d\n", __LINE__);
	// if (*argv == NULL)
	// {
		*argv = (t_argv *)malloc(sizeof(t_argv));
		(*argv)->str = new->str;
		(*argv)->flag = new->flag;
	// }
	// else
	// {
	// 	printf("%d\n", __LINE__);
	// 	tmp = (t_argv *)malloc(sizeof(t_argv));
	// 	tmp = *argv;
	// 	printf("%d\n", __LINE__);
	// 	while (tmp->next != NULL)
	// 		tmp = tmp->next;
	// 	printf("%d\n", __LINE__);
	// 	tmp->next->str = new->str;
	// 	tmp->next->flag = new->flag;
	// }
	printf("%d\n", __LINE__);
}

void	redir_lstadd(t_redir **redir, t_lexer *new)
{
	// t_redir	*tmp;

	*redir = (t_redir *)malloc(sizeof(t_redir));
	// if (*redir == NULL)
	// {
		(*redir)->str = new->str;
		(*redir)->flag = new->flag;
	// }
	// else
	// {
	// 	tmp = *redir;
	// 	while (tmp->next != NULL)
	// 		tmp = tmp->next;
	// 	tmp->next->str = new->str;
	// 	tmp->next->flag = new->flag;
	// }
	printf("%d\n", __LINE__);
}

int	redir_type(char *redir)
{
	int	i;

	if (redir == NULL)
		return (ERROR);
	i = 0;
	while (ft_isdigit(redir[i]))
		i++;
	if (redir[i] == '>' && redir[i + 1] == '\0')
		return (REDIR_OUT);
	else if (redir[i] == '>' && redir[i + 1] == '>')
		return (REDIR_OUT_APP);
	else if (redir[i] == '<' && redir[i + 1] == '\0')
		return (REDIR_IN);
	else if (redir[i] == '<' && redir[i + 1] == '<')
		return (REDIR_HEREDOC);
	else
		return (ERROR);
}
