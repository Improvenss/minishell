/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:45:12 by gsever            #+#    #+#             */
/*   Updated: 2022/10/05 16:49:37 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	token_is_cmd(t_list *token)
{
	if (token == NULL)
		return (false);
	if (token_content(token)->flags & (TOK_TEXT | TOK_REDIR))
		return (true);
	return (false);
}

/**
 * @brief Token->content'i dondurmesi icin kullaniyoruz.
 * 
 * @param token 
 * @return t_new_token* 
 */
t_new_token	*token_content(t_list *token)
{
	return ((t_new_token *)token->content);
}

/**
 * @brief Olusturulan new_token'i freelemek icin kullaniliyor.
 * 
 * @param new_token 
 */
void	new_token_destroy(void *new_token)
{
	free(((t_new_token *)new_token)->str);
	((t_new_token *)new_token)->str = NULL;
	free(new_token);
}

/**
 * @brief Yeni bir token olusturup next'ini NULL yapiyor.
 * 
 * @param string 
 * @param type 
 * @fn malloc()
 * @fn ft_lstnew() Burada yeni list'i olusturup icine yaziyore.
 * @return t_list* 
 */
t_list	*token_create(char *string, int type)
{
	t_new_token	*new;
	t_list		*token;

	new = malloc(sizeof(t_new_token));
	if (new == NULL)
		return (NULL);
	new->flags = type;
	new->str = string;
	token = ft_lstnew(new);
	if (token == NULL)
		return (NULL);
	token->next = NULL;
	return (token);
}
