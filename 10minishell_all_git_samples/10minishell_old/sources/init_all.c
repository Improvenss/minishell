/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:37:25 by gsever            #+#    #+#             */
/*   Updated: 2022/09/19 17:48:20 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
