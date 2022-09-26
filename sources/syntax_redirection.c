/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:35:16 by gsever            #+#    #+#             */
/*   Updated: 2022/09/25 14:08:55 by akaraca          ###   ########.fr       */
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
	int	x;

	i = 0;
	x = 0;
	while (base->input_line[i])
	{
		if (base->input_line[i] == '<' && look_the_quote(base->input_line, i))
		{
			if (base->input_line[i + 1] == '<' && base->input_line[i + 2] == '<')
				x = 1;
			else if (base->input_line[i + 1] == 32 && (base->input_line[i + 2] == '<'
				|| base->input_line[i + 2] == '>'))
				x = 1;
			else if (base->input_line[i + 1] == '>')
				x = 1;
			else if (base->input_line[i + 1] == '|' || base->input_line[i - 1] == '|')
				x = 1;
			else if (base->input_line[i + 1] == 32 && base->input_line[i + 2] == '|')
				x = 1;
			else if (base->input_line[i - 1] == 32 && base->input_line[i - 2] == '|')
				x = 1;
			else if (base->input_line[i + 1] == '\0')
				x = 1;
		}
		if (base->input_line[i] == '>' && look_the_quote(base->input_line, i))
		{
			if (base->input_line[i + 1] == '>' && base->input_line[i + 2] == '>')
				x = 1;
			else if (base->input_line[i + 1] == 32 && (base->input_line[i + 2] == '>'
				|| base->input_line[i + 2] == '<'))
				x = 1;
			else if (base->input_line[i + 1] == '<')
				x = 1;
			else if (base->input_line[i + 1] == '|' || base->input_line[i - 1] == '|')
				x = 1;
			else if (base->input_line[i + 1] == 32 && base->input_line[i + 2] == '|')
				x = 1;
			else if (base->input_line[i - 1] == 32 && base->input_line[i - 2] == '|')
				x = 1;
			else if (base->input_line[i + 1] == '\0')
				x = 1;
		}
		i++;
	}
	if (x == 1)
	{
		printf("Redirection: syntax error\n");
		return (-1);
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
int	redirection(t_base *base)
{
	if (syntax_left_right(base, -1) == -1)
		return (-1);
	return (1);
}