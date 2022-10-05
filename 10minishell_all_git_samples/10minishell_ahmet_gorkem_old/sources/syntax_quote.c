/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:06:45 by gsever            #+#    #+#             */
/*   Updated: 2022/09/28 14:25:48 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	single_double_quote(t_base *base, int i, char c)
{
	base->sq.first = i;
	base->sq.token = c;
	base->sq.lenght = ++i;
	base->sq.count++;
	while (base->input_line[base->sq.lenght])
	{
		if (base->input_line[base->sq.lenght] == c
			&& base->sq.last == 0)
		{
			base->sq.last = ++base->sq.lenght;
			base->sq.count++;
		}
		base->sq.lenght++;
	}
}

/**
 * @brief 
 * 
 * @nore
 * @param syntax 
 * @param i 
 * @return int 
 */
int	syntax_quote(t_base *base, int i)
{
	init_syntax_quote(base);
	while (base->input_line[i])
	{
		if (base->sq.token == '\0'
			&& (base->input_line[i] == '\''
				|| base->input_line[i] == '"'))
			single_double_quote(base, i, base->input_line[i]);
		i++;
	}
	if (base->sq.first != -1 && base->sq.last == 0)
		return (-1);
	if (base->sq.count == 0)
		return (ft_strlen(base->input_line));
	return (base->sq.last);
}

/**
 * @brief Tırnak yapısı kontrol ediliyor.
 * 
 * @fn ft_strlen()
 * @fn syntax_quote() Tırnak yapısının kontrolünü gerçekleştiriyor.
 * @fn printf()
 * @return int 
 */
int	quote(t_base *base)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(base->input_line);
	while (i != -1)
	{
		i = syntax_quote(base, i);
		if (i == -1)
		{
			printf("quote: Syntax Error!\n");
			return (0);
		}
		if (i == l)
			return (1);
	}
	return (1);
}
