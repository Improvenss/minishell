/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_ampersand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:36:39 by gsever            #+#    #+#             */
/*   Updated: 2022/09/26 17:58:35 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ampersand(t_base *base)
{
	int	i;

	i = -1;
	while (base->input_line[++i] != '\0')
	{
		if (base->input_line[i] == '&' && base->input_line[i + 1] == '&'
			&& base->input_line[i + 2] == '&' && (base->input_line[i + 3] == 32
			|| base->input_line[i + 3] == '\0'))
		{
			printf("syntax error near unexpected token `&&'\n");
			return (0);
		}
	}
	return (1);
}
