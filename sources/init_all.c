/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:45:41 by gsever            #+#    #+#             */
/*   Updated: 2022/09/23 18:33:01 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 */
void	init_syntax(t_base *base)
{
	base->syntax_token = '\0';
	base->syntax_first = -1;
	base->syntax_last = 0;
	base->syntax_lenght = 0;
	base->syntax_count = 0;
}