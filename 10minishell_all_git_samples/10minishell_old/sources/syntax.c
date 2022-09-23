/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:41:13 by gsever            #+#    #+#             */
/*   Updated: 2022/09/23 18:35:05 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Kaçış operatörü kontrol edilir.
 * 
 * 	Operatörden sonra EOF var ise hatalıdır.
 * @return int 
 */
int	ft_escape(void)
{
	int	i;

	i = 0;
	while (g_main.input_line[i])
	{
		if (g_main.input_line[i] == SHELL_ESCAPE[0] && g_main.input_line[i + 1] == '\0')
		{
			printf("Syntax Error\n");
			return (-1);
		}
		i++;
	}
	return (1);
}

/**
 * @brief Left, Right ve Heredoc operatörlerinin yapısı kontrol edilir.
 * 
 * @fn syntax_left_right()
 * @fn syntax_heredoc()
 * @return int 
 */
int	ft_redirection(void)
{
	if (syntax_left_right() == -1 || syntax_heredoc() == -1)
		return (-1);
	return (1);
}

/**
 * @brief Pipe operatörünün sol ve sağ durumu kontrol edilir.
 * 
 * @fn ft_strlen()
 * @fn syntax_pipe()
 * @fn printf()
 * @return int 
 */
int	ft_pipe(void)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(g_main.input_line);
	while (i != -1)
	{
		i = syntax_pipe(i);
		if (i == -1)
		{
			printf("syntax error near unexpected token `|'\n");
			return (0);
		}
		if (i == l)
			return (1);
	}
	return (1);
}

/**
 * @brief Tırnak yapısı kontrol ediliyor.
 * 
 * @fn ft_strlen()
 * @fn syntax_quote() Tırnak yapısının kontrolünü gerçekleştiriyor.
 * @fn printf()
 * @return int 
 */
int	ft_quote(void)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(g_main.input_line);
	while (i != -1)
	{
		i = syntax_quote(i);
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

/**
 * @brief Girdinin işleme alınmadan önce 
 * 	belirli kurallara uygunmu kontrol ediliyor.
 * 
 * @fn ft_quote()
 * @return int
 */
int	syntax(void)
{
	if (ft_quote() == 1 && ft_redirection() == 1 && ft_pipe() == 1 && ft_escape() == 1)
		return (1);
	return (0);
}
