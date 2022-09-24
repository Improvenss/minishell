/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:06:45 by gsever            #+#    #+#             */
/*   Updated: 2022/09/24 13:37:04 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	single_double_quote(t_base *base, int i, char c)
{
	base->syntax_first = i;
	base->syntax_token = c;
	base->syntax_lenght = ++i;
	base->syntax_count++;
	while (base->input_line[base->syntax_lenght])
	{
		if (base->input_line[base->syntax_lenght] == c
			&& base->syntax_last == 0)
		{
			base->syntax_last = ++base->syntax_lenght;
			base->syntax_count++;
		}
		base->syntax_lenght++;
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
	init_syntax(base);
	while (base->input_line[i])
	{
		if (base->syntax_token == '\0'
			&& (base->input_line[i] == '\''
			|| base->input_line[i] == '"'))
			single_double_quote(base, i, base->input_line[i]);
		i++;
	}
	if (base->syntax_first != -1 && base->syntax_last == 0)
		return (-1);
	if (base->syntax_count == 0)
		return (ft_strlen(base->input_line));
	return (base->syntax_last);
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
