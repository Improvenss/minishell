/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:15:03 by akaraca           #+#    #+#             */
/*   Updated: 2022/09/20 16:59:33 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_heredoc(void)
{
	
	return (1);
}

int	syntax_right(void)
{
	int		i;
	int		k;
	int		first;
	char	token;

	i = 0;
	k = 0;
	first = 0;
	token = '\0';
	while (g_main.input_line[i])
	{
		if (token == '\0' && g_main.input_line[i] == '>')
		{
			token = '>';
			first = i;
		}
		if (token != '\0' && (g_main.input_line[i + 2] == '>' || g_main.input_line[i + 2] == '<'))
		{
			if (g_main.input_line[i + 3] == '>' || g_main.input_line[i + 3] == '<')
				printf("right: syntax error near unexpected token `%c%c'\n", g_main.input_line[i + 2], g_main.input_line[i + 3]);
			else
				printf("right: syntax error near unexpected token `%c'\n", g_main.input_line[i + 2]);
			return (-1);
		}
		i++;
	}
	return (1);
}

int	syntax_left(void)
{
	int		i;
	int		k;
	int		first;
	char	token;

	i = 0;
	k = 0;
	first = 0;
	token = '\0';
	while (g_main.input_line[i])
	{
		if (token == '\0' && g_main.input_line[i] == '<')
		{
			token = '<';
			first = i;
		}
		if (token != '\0' && g_main.input_line[i + 1] == '|')
		{
			if (g_main.input_line[i + 2] == '|')
				printf("left: syntax error near unexpected token `||'\n");
			else
				printf("left: syntax error near unexpected token `|'\n");
			return (-1);
		}
		if (token != '\0' && (g_main.input_line[i + 2] == '>' || g_main.input_line[i + 2] == '<'))
		{
			if (g_main.input_line[i + 3] == '|')
			{
				printf("left: syntax error near unexpected token `>|'\n");
			}
			else if (g_main.input_line[i + 3] == '>' || g_main.input_line[i + 3] == '<')
			{
				printf("left: syntax error near unexpected token `%c%c'\n", g_main.input_line[i + 3], g_main.input_line[i + 3]);
			}
			else
				printf("left: syntax error near unexpected token `%c'\n", g_main.input_line[i + 2]);
			return (-1);
		}
		if (g_main.input_line[i] == 32)
			k++;
		i++;
	}
	if (k == i - first - 1)
	{
		if (g_main.input_line[first - 2] != '>')
		{
			printf("left: syntax error near unexpected token `newline'\n");
			return (-1);
		}
	}
	return (1);
}

/**
 * @brief 
 * 	"<" operatörünün sağı EOF olmamalıdır. (newline)
 * 		"< >|"		hatalı bir yapıdır. (>|)	√
 * 		"<|"		hatalı bir yapıdır. (|)		√
 * 		"<		|"	hatalı bir yapıdır. (|)		√
 * 		"<||"		hatalı bir yapıdır. (||)	√
 * 		"<		>>"	hatalı bir yapıdır. (>>)	√
 *		"<		<<"	hatalı bir yapıdır. (<<)	√
 * 		"<		>"	hatalı bir yapıdır. (>)		√
 * 		"<		<"	hatalı bir yapıdır. (<)		√
 *		"<>>"		hatalı bir yapıdır. (>)		√
 * 	">" operatörünün sağı EOF olmamalıdır. (newline)
 * 		"> |"		hatalı bir yapıdır. (|) (arada boş karakter olmalıdır.)
 * 		">		>>"	hatalı bir yapıdır. (>>)	
 * 		">		<<"	hatalı bir yapıdır. (<<)	
 * 		"><<"		hatalı bir yapıdır. (<<)	
 * 		">		>"	hatalı bir yapıdır. (>)		
 * 		"><"		hatalı bir yapıdır. (<)		
 * 		">		<"	hatalı bir yapıdır. (<)		
 * 		">		<>"	hatalı bir yapıdır. (<>)	
 * 		"><>"		hatalı bir yapıdır. (<>)	
 * 	"\" kaçış metasını görmelidir. Duruma göre dize olarak betimleniyor.
 * 	Tırnak operatörlerini görmelidir.
 * 
 * @return int 
 */
int	syntax_left_right(void)
{
	if (syntax_left() == -1 || syntax_right() == -1)
		return (-1);
	return (1);
}
