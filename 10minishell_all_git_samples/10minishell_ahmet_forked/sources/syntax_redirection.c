/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:15:03 by akaraca           #+#    #+#             */
/*   Updated: 2022/09/21 15:34:56 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_heredoc(void)
{
	
	return (1);
}

/**
 * @brief 
 * 	"<" operatörünün sağı EOF olmamalıdır. (newline)	✓
 * 		"<>"		hatalı bir yapıdır. (newline)		✓
 * 		"< >|"		hatalı bir yapıdır. (>|)			✓
 * 		"<>|"		hatalı bir yapıdır. (|)				✓
 * 		"<>||"		hatalı bir yapıdır. (||)			✓
 * 		"<||"		hatalı bir yapıdır. (||)			✓
 * 		"<|"		hatalı bir yapıdır. (|)				✓
 * 		"<>		|"	hatalı bir yapıdır. (|)				✓
 * 		"<		|"	hatalı bir yapıdır. (|)				✓
 * 		"<		>>"	hatalı bir yapıdır. (>>)			✓
 *		"<>>"		hatalı bir yapıdır. (>)				✓
 *		"<		<<"	hatalı bir yapıdır. (<<)			✓
 * 		"<		>"	hatalı bir yapıdır. (>)				✓
 * 		"<		<"	hatalı bir yapıdır. (<)				✓
 * 	">" operatörünün sağı EOF olmamalıdır. (newline)	✓
 * 		"> |"		hatalı bir yapıdır. (|)				✓
 * 		">		>>"	hatalı bir yapıdır. (>>)			✓
 * 		">		<<"	hatalı bir yapıdır. (<<)			✓
 * 		"><<"		hatalı bir yapıdır. (<<)			✓
 * 		">		>"	hatalı bir yapıdır. (>)				✓
 * 		"><"		hatalı bir yapıdır. (<)				✓
 * 		">		<"	hatalı bir yapıdır. (<)				✓
 * 		">		<>"	hatalı bir yapıdır. (<>)			✓
 * 		"><>"		hatalı bir yapıdır. (<>)			✓
 * 	"\" kaçış metasını görmelidir. Duruma göre dize olarak betimleniyor.
 * 	Tırnak operatörlerini görmelidir.
 * 
 * @return int 
 */
int	syntax_left_right(void)
{
	int		i;
	int		k;
	int		first;
	char	token;
	int		l;

	i = 0;
	k = 0;
	first = 0;
	l = ft_strlen(g_main.input_line);
	token = '\0';
	while (g_main.input_line[i])
	{
		if (token == '\0' && (g_main.input_line[i] == '<' || g_main.input_line[i] == '>') && look_the_quote(g_main.input_line, i))
		{
			token = g_main.input_line[i];
			first = i;
		}
		if (token != '\0' && (g_main.input_line[first + 1] == '>' || g_main.input_line[first + 1] == '<'))
		{
			if (token == '>' && g_main.input_line[first + 1] == '<')
				k = first + 1;
			else
				k = first + 2;
			while (g_main.input_line[k] && k <= l && g_main.input_line[k] == 32)
				k++;
			if (g_main.input_line[k] == '|' || g_main.input_line[k] == '<' || g_main.input_line[k] == '>')
			{
				if (g_main.input_line[k + 1] == '|' || g_main.input_line[k + 1] == '<' || g_main.input_line[k + 1] == '>')
					printf("left: syntax error near unexpected token `%c%c'\n", g_main.input_line[k], g_main.input_line[k + 1]);
				else
					printf("left: syntax error near unexpected token `%c'\n", g_main.input_line[k]);
				return (-1);
			}
			else if (g_main.input_line[k] == '\0')
			{
				printf("left: syntax error near unexpected token `newline'\n");
				return (-1);
			}
			else
			{
				token = '\0';
				i = k;
			}
		}
		if (token != '\0' && (g_main.input_line[i] == '>' || g_main.input_line[i] == '<' || g_main.input_line[i] == '|'))
		{
			k = first + 1;
			while (g_main.input_line[k] && k <= l && g_main.input_line[k] == 32)
				k++;
			if (g_main.input_line[k] == '|' || g_main.input_line[k] == '<' || g_main.input_line[k] == '>')
			{
				if (g_main.input_line[k + 1] == '|' || g_main.input_line[k + 1] == '<' || g_main.input_line[k + 1] == '>')
					printf("left: syntax error near unexpected token `%c%c'\n", g_main.input_line[k], g_main.input_line[k + 1]);
				else
					printf("left: syntax error near unexpected token `%c'\n", g_main.input_line[k]);
				return (-1);
			}
			else if (g_main.input_line[k] == '\0')
			{
				printf("left: syntax error near unexpected token `newline'\n");
				return (-1);
			}
			else
			{
				token = '\0';
				i = k;
			}
		}
		i++;
	}
	return (1);
}
