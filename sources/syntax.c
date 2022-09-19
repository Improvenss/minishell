/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:41:13 by gsever            #+#    #+#             */
/*   Updated: 2022/09/19 14:37:58 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_run(void)
{
	printf("Çalışıyor.\n");
}

void	double_quote(int i)
{
	g_main.syntax.first = i;
	g_main.syntax.token = SHELL_QUOTE_CHARS[1];
	g_main.syntax.lenght = ++i;
	g_main.syntax.count++;
	while (g_main.input_line[g_main.syntax.lenght])
	{
		if (g_main.input_line[g_main.syntax.lenght]
			== SHELL_QUOTE_CHARS[1]
			&& g_main.syntax.last == 0
			&& g_main.input_line[g_main.syntax.lenght - 1]
			!= SHELL_ESCAPE[0])
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
	g_main.syntax.token = SHELL_QUOTE_CHARS[0];
	g_main.syntax.lenght = ++i;
	g_main.syntax.count++;
	while (g_main.input_line[g_main.syntax.lenght])
	{
		if (g_main.input_line[g_main.syntax.lenght]
			== SHELL_QUOTE_CHARS[0] && g_main.syntax.last == 0)
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
int	syntax_loop(int i)
{
	init_syntax();
	while (g_main.input_line[i])
	{
		if (g_main.syntax.token == '\0' && g_main.input_line[i]
			== SHELL_QUOTE_CHARS[0]
			&& g_main.input_line[i - 1] != SHELL_ESCAPE[0])
			single_quote(i);
		else if (g_main.syntax.token == '\0' && g_main.input_line[i]
			== SHELL_QUOTE_CHARS[1]
			&& g_main.input_line[i - 1] != SHELL_ESCAPE[0])
			double_quote(i);
		i++;
	}
	if (g_main.syntax.first != -1 && g_main.syntax.last == 0)
		return (-1);
	if (g_main.syntax.count == 0)
		return (ft_strlen(g_main.input_line));
	return (g_main.syntax.last);
}

/**
 * @brief 
 * 
 * @fn ft_strlen()
 * @fn syntax_loop()
 * @fn printf()
 * @return int 
 */
int	syntax(void)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(g_main.input_line);
	while (i != -1)
	{
		i = syntax_loop(i);
		if (i == -1)
		{
			printf("Syntax Error!\n");
			return (0);
		}
		if (i == l)
			return (1);
	}
	return (1);
}
