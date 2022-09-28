/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:45:41 by gsever            #+#    #+#             */
/*   Updated: 2022/09/28 14:36:54 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_syntax_brackets(t_base *base)
{
	base->sb.base = base;
	base->sb.token = '\0';
	base->sb.left = 0;
	base->sb.right = 0;
	base->sb.last = 0;
}

/**
 * @brief 
 * 
 */
void	init_syntax_quote(t_base *base)
{
	base->sq.base = base;
	base->sq.token = '\0';
	base->sq.first = -1;
	base->sq.last = 0;
	base->sq.lenght = 0;
	base->sq.count = 0;
}
