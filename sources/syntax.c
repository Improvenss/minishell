/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:15:13 by gsever            #+#    #+#             */
/*   Updated: 2022/09/27 12:27:37 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	white_space(t_base *base)
{
	int	i;

	i = 0;
	while (base->input_line[i])
	{
		if (base->input_line[i] > 127 || base->input_line[i] < 0)
		{
			printf("Whitespace: Syntax Error! (%d)\n", i);
			return (-1);
		}
		i++;
	}
	return (1);
}

/**
 * @brief Girdinin işleme alınmadan önce 
 * 	belirli kurallara uygunmu kontrol ediliyor.
 * 
 * @return int
 */
int	syntax(t_base *base)
{
	base->input_line = delete_space(base->input_line, 0, 0, 0);
	if (quote(base) == 1 && the_pipe(base) == 1 && redirection(base)
		== 1 && brackets(base) == 1 && white_space(base) == 1
		&& ampersand(base) == 1)
		return (1);
	return (0);
}
