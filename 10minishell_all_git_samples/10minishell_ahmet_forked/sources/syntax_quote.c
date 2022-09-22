/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:41:13 by gsever            #+#    #+#             */
/*   Updated: 2022/09/19 18:08:56 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	double_quote(int i)
{
	g_main.syntax.first = i;
	g_main.syntax.token = '"';
	g_main.syntax.lenght = ++i;
	g_main.syntax.count++;
	while (g_main.input_line[g_main.syntax.lenght])
	{
		if (g_main.input_line[g_main.syntax.lenght]
			== '"'
			&& g_main.syntax.last == 0
			&& g_main.input_line[g_main.syntax.lenght - 1]
			!= '\'')
		{
			g_main.syntax.last = ++g_main.syntax.lenght;
			g_main.syntax.count++;
		}
		g_main.syntax.lenght++;
	}
}

void	single_quote(int i)
{
	g_main.syntax.first = i;
	g_main.syntax.token = '\'';
	g_main.syntax.lenght = ++i;
	g_main.syntax.count++;
	while (g_main.input_line[g_main.syntax.lenght])
	{
		if (g_main.input_line[g_main.syntax.lenght]
			== '\'' && g_main.syntax.last == 0)
		{
			g_main.syntax.last = ++g_main.syntax.lenght;
			g_main.syntax.count++;
		}
		g_main.syntax.lenght++;
	}
}

/**
 * @brief 
 * 
 * while->if->while->if Tek tırnak içerisinde kaçış metası yok sayılıyor
 * 	bu yüzden buraya eklemeye gerek yok.
 * 
 * @param i 
 * @return int 
 */
int	syntax_quote(int i)
{
	init_syntax();
	while (g_main.input_line[i])
	{
		if (g_main.syntax.token == '\0' && g_main.input_line[i]
			== '\''
			&& g_main.input_line[i - 1] != '\\')
			single_quote(i);
		else if (g_main.syntax.token == '\0' && g_main.input_line[i]
			== '"'
			&& g_main.input_line[i - 1] != '\\')
			double_quote(i);
		i++;
	}
	if (g_main.syntax.first != -1 && g_main.syntax.last == 0)
		return (-1);
	if (g_main.syntax.count == 0)
		return (ft_strlen(g_main.input_line));
	return (g_main.syntax.last);
}
