/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_ampersand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:36:39 by gsever            #+#    #+#             */
/*   Updated: 2022/09/27 12:27:28 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 1 tane '&' varsa yok sayilacak, pdf'de oyle yaziyor. 2 tane '&&'
 * 	varsa calisacak. 3+ tane varsa error dondurecek.
 * 
 * @param base main structure for 'input_line'.
 * @return int 
 */
int	ampersand(t_base *base)
{
	int	i;

	i = -1;
	while (base->input_line[++i] != '\0')
	{
		if (base->input_line[i] == '&' && base->input_line[i + 1] == '&'
			&& base->input_line[i + 2] == '&' && base->input_line[i + 3] == '&')
		{
			printf("syntax error near unexpected token `&&'\n");
			return (0);
		}
		else if (base->input_line[i] == '&' && base->input_line[i + 1] == '&'
			&& base->input_line[i + 2] == '&')
		{
			printf("syntax error near unexpected token `&'\n");
			return (0);
		}
	}
	return (1);
}
