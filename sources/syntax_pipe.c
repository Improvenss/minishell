/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:59:23 by gsever            #+#    #+#             */
/*   Updated: 2022/09/27 17:21:34 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 * 1.if: '||'
 * 2.if: '|||' veya '|| |'
 * 3.if: '| |'
 * 
 * @param base 
 * @param i 
 * @fn look_the_quote()
 * @return int 
 */
int	syntax_pipe_first_half(t_base *base, int i)
{
	if (base->input_line[i] == '|' && base->input_line[i + 1]
		== '|' && look_the_quote(base->input_line, i))
	{
		if (base->input_line[i + 2] == '|' || (base->input_line[i + 3]
				== '|' && base->input_line[i + 2]
				== 32 && look_the_quote(base->input_line, i)))
			return (0);
	}
	if (base->input_line[i] == '|' && base->input_line[i + 1] == 32
		&& base->input_line[i + 2] == '|'
		&& look_the_quote(base->input_line, i))
		return (0);
	return (1);
}

/**
 * @brief 
 * 
 * 4.if: '|)' veya '| )' hatalı bir kullanımdır.
 * 5.if: '(|' veya '( |' hatalı bir kullanımdır.
 * 
 * @param base 
 * @param i 
 * @fn look_the_quote()
 * @return int 
 */
int	syntax_pipe_last_half(t_base *base, int i)
{
	if (base->input_line[i] == '|' && (base->input_line[i + 1] == ')'
			|| (base->input_line[i + 1] == 32
				&& base->input_line[i + 2] == ')'))
		&& look_the_quote(base->input_line, i))
		return (0);
	if (base->input_line[i] == '|' && (base->input_line[i - 1] == '('
			|| (base->input_line[i - 1] == 32
				&& base->input_line[i - 2] == '('))
		&& look_the_quote(base->input_line, i))
		return (0);
	return (1);
}

/**
 * @brief 
 * 


 * 
 * @param base 
 * @param i 
 * @return int 
 */
int	syntax_pipe(t_base *base, int i)
{
	while (base->input_line[i])
	{
		if (syntax_pipe_first_half(base, i) == 0)
			return (0);
		if (syntax_pipe_last_half(base, i) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	the_pipe(t_base *base)
{
	if (base->input_line[0] == '|'
		|| base->input_line[ft_strlen(base->input_line) - 1] == '|'
		|| !syntax_pipe(base, 0))
		printf("pipe: Syntax Error!\n");
	else
		return (1);
	return (0);
}
