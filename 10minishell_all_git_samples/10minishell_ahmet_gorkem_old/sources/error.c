/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:38:56 by gsever            #+#    #+#             */
/*   Updated: 2022/09/30 15:45:39 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Printing all error messages.
 * 
 * @def ERROR: = -1
 * @param s1 
 * @param s2 
 * @param s3 
 * @param message 
 * @fn ft_putstr_fd() 
 * @return int 
 */
int	print_error(char *s1, char *s2, char *s3, char *message)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
	{
		if (s1)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s2, 2);
	}
	if (s3)
	{
		if (s1 || s2)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s3, 2);
	}
	if (message)
	{
		if (s1 || s2 || s3)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	ft_putchar_fd('\n', 2);
	return (ERROR);
}