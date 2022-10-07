/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:35:33 by gsever            #+#    #+#             */
/*   Updated: 2022/10/06 13:16:44 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Disaridan (token list'ten hesaplanarak) gelen scmd'imizi burada
 *  new_ struct'una ekliyor.
 * 
 * @param type 
 * @return t_list* 
 */
t_list	*scmd_create(int type)
{
	t_c_scmd	*c_scmd;
	t_list		*scmd;

	c_scmd = malloc(sizeof(t_c_scmd));
	if (c_scmd == NULL)
		return (NULL);
	c_scmd->type = type;
	c_scmd->l_argv = NULL;
	c_scmd->l_redir = NULL;
	scmd = ft_lstnew(c_scmd);
	if (scmd == NULL)
	{
		c_scmd_destroy(c_scmd);
		return (NULL);
	}
	scmd->next = NULL;
	return (scmd);
}

/**
 * @brief t_list tipinden gelen structtan t_c_scmd tipinden return aliyor.
 * 
 * @param scmd 
 * @return t_c_scmd* 
 */
t_c_scmd	*scmd_content(t_list *scmd)
{
	return ((t_c_scmd *)scmd->content);
}

/**
 * @brief scmd'leri aldiktan sonra isi bitmis tokenleri destroyluyor.
 * 
 * @param c_scmd 
 */
void	c_scmd_destroy(void *c_scmd)
{
	if (((t_c_scmd *)c_scmd)->l_argv)
		ft_lstclear(&(((t_c_scmd *)c_scmd)->l_argv), new_token_destroy);
	if (((t_c_scmd *)c_scmd)->l_redir)
		ft_lstclear(&(((t_c_scmd *)c_scmd)->l_redir), new_token_destroy);
	free(c_scmd);
}