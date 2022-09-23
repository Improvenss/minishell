/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:35:16 by gsever            #+#    #+#             */
/*   Updated: 2022/09/23 19:37:27 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 * @param base 
 * @param i 
 * @fn look_the_quote() Op. tırnak içerisinde ise if'e girmeyecek.
 * @return int 
 */
int	syntax_left_right(t_base *base, int i)
{
	int		k;
	int		first;
	char	token;
	int		l;

	i = 0;
	k = 0;
	first = 0;
	l = ft_strlen(base->input_line);
	token = '\0';
	while (base->input_line[i])
	{
		if (token == '\0' && (base->input_line[i] == '<' || base->input_line[i] == '>') && look_the_quote(base->input_line, i))
		{
			if (base->input_line[i - 1] != '\\' || (base->input_line[i - 1] == '\\' && base->input_line[i - 2] == '\\')) // "\\<" girdisi yapıldığında backslahlar birbirini ignorluyor, "\<" yapıldığında ise operator ignorlanıyor
			{
				token = base->input_line[i];
				first = i;
			}
		}
		if (token != '\0' && (base->input_line[first + 1] == '>' || base->input_line[first + 1] == '<'))
		{
			if (token == '>' && base->input_line[first + 1] == '<')
				k = first + 1;
			else
				k = first + 2;
			while (base->input_line[k] && k <= l && base->input_line[k] == 32)
				k++;
			if (base->input_line[k] == '|' || base->input_line[k] == '<' || base->input_line[k] == '>')
			{
				if (base->input_line[k + 1] == '|' || base->input_line[k + 1] == '<' || base->input_line[k + 1] == '>')
					printf("left: syntax error near unexpected token `%c%c'\n", base->input_line[k], base->input_line[k + 1]);
				else
					printf("left: syntax error near unexpected token `%c'\n", base->input_line[k]);
				return (-1);
			}
			else if (base->input_line[k] == '\0')
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
		if (token != '\0' && (base->input_line[i] == '>' || base->input_line[i] == '<' || base->input_line[i] == '|'))
		{
			k = first + 1;
			while (base->input_line[k] && k <= l && base->input_line[k] == 32)
				k++;
			if (base->input_line[first + 1] != '|' && (base->input_line[k] == '|' || base->input_line[k] == '<' || base->input_line[k] == '>')) //base->input_line[first + 1] != '|' --> ">|" durum için özel.
			{
				if (base->input_line[k + 1] == '|' || base->input_line[k + 1] == '<' || base->input_line[k + 1] == '>')
					printf("left: syntax error near unexpected token `%c%c'\n", base->input_line[k], base->input_line[k + 1]);
				else
					printf("left: syntax error near unexpected token `%c'\n", base->input_line[k]);
				return (-1);
			}
			else if (base->input_line[first + 1] == '|') 
			{
				if ((base->input_line[first + 2] == '<' || base->input_line[first + 2] == '>')) // <|< b, değeri hata döndürmüyordu.
					printf("left: syntax error near unexpected token `|'\n");
				else if (base->input_line[first + 2] != '<' || base->input_line[first + 2] != '>') // "<| a" değeri hata döndürmüyordu.
					printf("left: syntax error near unexpected token `|'\n");
				return (-1);
			}
			else if (base->input_line[k] == '\0')
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
	/*int		k;
	int		first;
	char	token;
	int		l;

	i = 0;
	k = 0;
	first = 0;
	l = ft_strlen(base->input_line);
	token = '\0';
	while (base->input_line[++i])
	{
	if (token == '\0' && (base->input_line[i] == '<' || base->input_line[i] == '>') && look_the_quote(base->input_line, i))
		{
			token = base->input_line[i];
			first = i;
		}
		if (token != '\0' && (base->input_line[first + 1] == '>' || base->input_line[first + 1] == '<'))
		{
			if (token == '>' && base->input_line[first + 1] == '<')
				k = first + 1;
			else
				k = first + 2;
			while (base->input_line[k] && k <= l && base->input_line[k] == 32)
				k++;
			if (base->input_line[k] == '|' || base->input_line[k] == '<' || base->input_line[k] == '>')
			{
				if (base->input_line[k + 1] == '|' || base->input_line[k + 1] == '<' || base->input_line[k + 1] == '>')
					printf("redirection: syntax error near unexpected token `%c'\n", base->input_line[k]);
				return (-1);
			}
			else if (base->input_line[k] == '\0')
			{
					printf("redirection: syntax error near unexpected token `newline'\n");
				return (-1);
			}
			else
			{
				token = '\0';
				i = k;
			}
		}
		if (token != '\0' && (base->input_line[i] == '>' || base->input_line[i] == '<' || base->input_line[i] == '|'))
		{
			k = first + 1;
			while (base->input_line[k] && k <= l && base->input_line[k] == 32)
				k++;
			if (base->input_line[k] == '|' || base->input_line[k] == '<' || base->input_line[k] == '>')
			{
				if (base->input_line[k + 1] == '|' || base->input_line[k + 1] == '<' || base->input_line[k + 1] == '>')
					printf("redirection: syntax error near unexpected token `%c'\n", base->input_line[k]);
				return (-1);
			}
			else if (base->input_line[k] == '\0')
			{
				printf("redirection: syntax error near unexpected token `newline'\n");
				return (-1);
			}
			else
			{
				token = '\0';
				i = k;
			}
		}
	}
	return (1);*/
}

/**
 * @brief Left, Right ve Heredoc operatörlerinin yapısı kontrol edilir.
 * 
 * @fn syntax_left_right()
 * @fn syntax_heredoc()
 * @return int 
 */
int	redirection(t_base *base)
{
	if (syntax_left_right(base, -1) == -1)
		return (-1);
	return (1);
}