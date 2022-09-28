/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:42:34 by akaraca           #+#    #+#             */
/*   Updated: 2022/09/28 14:54:11 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 
 * @param base 
 * @param i 
 * @param err 
 * @fn look_the_quote() Op. tırnak içerisinde ise if'e girmeyecek.
 * @return int 
 */
int	syntax_right(t_base *base, int i, int err)
{
	if (base->input_line[i] == '>' && look_the_quote(base->input_line, i))
	{
		if (base->input_line[i + 1] == '>' && base->input_line[i + 2] == '>')
			err = 0;
		if (base->input_line[i + 1] == 32 \
		&& (base->input_line[i + 2] == '>' || base->input_line[i + 2] == '<'))
			err = 0;
		if (base->input_line[i + 1] == '<')
			err = 0;
		if (base->input_line[i + 1] == '|' || base->input_line[i - 1] == '|')
			err = 0;
		if (base->input_line[i + 1] == 32 && base->input_line[i + 2] == '|')
			err = 0;
		if (base->input_line[i - 1] == 32 && base->input_line[i - 2] == '|')
			err = 0;
		if (base->input_line[i + 1] == '\0' \
		|| (base->input_line[i + 1] == 32 && base->input_line[i + 2] == '\0'))
			err = 0;
	}
	return (err);
}

/**
 * @brief 
 * 
 * @param base 
 * @param i 
 * @param err 
 * @fn look_the_quote() Op. tırnak içerisinde ise if'e girmeyecek.
 * @return int 
 */
int	syntax_left(t_base *base, int i, int err)
{
	if (base->input_line[i] == '<' && look_the_quote(base->input_line, i))
	{
		if (base->input_line[i + 1] == '<' && base->input_line[i + 2] == '<')
			err = 0;
		if (base->input_line[i + 1] == 32 \
		&& (base->input_line[i + 2] == '<' || base->input_line[i + 2] == '>'))
			err = 0;
		if (base->input_line[i + 1] == '>')
			err = 0;
		if (base->input_line[i + 1] == '|' || base->input_line[i - 1] == '|')
			err = 0;
		if (base->input_line[i + 1] == 32 && base->input_line[i + 2] == '|')
			err = 0;
		if (base->input_line[i - 1] == 32 && base->input_line[i - 2] == '|')
			err = 0;
		if (base->input_line[i + 1] == '\0' \
		|| (base->input_line[i + 1] == 32 && base->input_line[i + 2] == '\0'))
			err = 0;
	}
	return (err);
}

/**
 * @brief Left, Right ve Heredoc operatörlerinin yapısı kontrol edilir.
 * 
 * @fn syntax_left_right()
 * @return int 
 */
int	redirection(t_base *base)
{
	int	i;
	int	err;

	i = 0;
	err = 1;
	while (base->input_line[i])
	{
		err = syntax_left(base, i, err);
		err = syntax_right(base, i, err);
		i++;
	}
	if (err == 0)
	{
		printf("Redirection: syntax error\n");
		return (err);
	}
	return (err);
}
