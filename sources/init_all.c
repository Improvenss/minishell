/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:37:25 by gsever            #+#    #+#             */
/*   Updated: 2022/09/19 14:37:55 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 */
void	init_syntax(void)
{
	g_main.syntax.token = '\0';
	g_main.syntax.first = -1;
	g_main.syntax.last = 0;
	g_main.syntax.lenght = 0;
	g_main.syntax.count = 0;
}
