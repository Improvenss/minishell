/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:58:09 by gsever            #+#    #+#             */
/*   Updated: 2022/10/06 13:46:01 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief tokenleri scmd'ye atiyor.
 * 
 * @param c_scmd 
 * @param l_token 
 * @return int 
 */
static int	scmd_token_set(t_c_scmd *c_scmd, t_list **l_token)
{
	t_list	*next;

	while (cmd_type_from_token(*l_token) == CMD_SCMD)
	{
		next = (*l_token)->next;
		if (token_content(*l_token)->flags & TOK_REDIR)
		{
			if (redir_type(token_content(*l_token)->str) == REDIR_HEREDOC)
			{
				if (parser_heredoc(*l_token) == ERROR)
					return (ERROR);
			}
			ft_lstadd_back(&(c_scmd->l_redir), *l_token);
		}
		else if (token_content(*l_token)->flags & TOK_REDIR_FILE)
			ft_lstadd_back(&(c_scmd->l_redir), *l_token);
		else
			ft_lstadd_back(&(c_scmd->l_argv), *l_token);
		(*l_token)->next = NULL;
		*l_token = next;
	}
	return (0);
}

/**
 * @brief 
 * 
 * @param l_token 
 * @return t_list* 
 */
t_list	*parser_scmd_tokens(t_list *l_token)
{
	t_list	*l_scmd;
	t_list	*scmd;
	// t_list	*next;

	l_scmd = NULL;
	while (l_token != NULL)
	{
		scmd = scmd_create(cmd_type_from_token(l_token));
		if (scmd == NULL
			|| (scmd_content(scmd)->type == CMD_SCMD
				&& scmd_token_set(scmd_content(scmd), &l_token) == ERROR))
		{
			ft_lstclear(&l_scmd, c_scmd_destroy);
			return (NULL);
		}
		ft_lstadd_back(&l_scmd, scmd);
	}
	return (l_scmd);
}

void AAA(t_c_cmd *tmp)
{
	printf("type: %d\n", tmp->type);
}

/**
 * @brief Tokenli listemizi alip, hangi command var onlari bulup yaziyor.
 * 
 * @param l_token 
 * @fn parser_scmd_tokens()
 * @return t_list* 
 */
t_list	*parser(t_list *l_token)
{
	t_list	*l_cmd;

	l_cmd = parser_scmd_tokens(l_token);
	if (l_cmd == NULL)
		return (NULL);

	
	t_list *tmp = l_cmd;
	while (tmp)
	{
		AAA(tmp->content);
		tmp = tmp->next;
	}
	return (l_cmd);
}