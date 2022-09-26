/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:45:41 by gsever            #+#    #+#             */
/*   Updated: 2022/09/25 13:41:39 by akaraca          ###   ########.fr       */
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