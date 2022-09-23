/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:15:13 by gsever            #+#    #+#             */
/*   Updated: 2022/09/23 19:29:21 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Girdinin işleme alınmadan önce 
 * 	belirli kurallara uygunmu kontrol ediliyor.
 * 
 * @return int
 */
int	syntax(t_base *base)
{
	base->input_line = delete_space(base->input_line, 0, 0, 0);
	if (quote(base) == 1 && redirection(base) == 1)
		return (1);
	return (0);
}
