/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:24:49 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/13 13:11:49 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief str1: str:2 str:3 message: and added newline(\\n).
 * 
 * @param s1 Usually for SHELL_NAME
 * @param s2 Usually command string.
 * @param s3 If have more command string or message.
 * @param message Usually command information.
 * @fn ft_putstr_fd(): For string message.
 * @fn ft_putchar_fd(): For '\n'.
 * @return int ERROR -> -1
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

/**
 * @brief Printing error with number.
 * NOT: #include <error.h> -> error = 0; da tanimlanan
 *  error'u 0 yapiyor.
 * @param s1 
 * @param s2 
 * @param s3 
 * @fn print_error(): For print error.
 * @fn strerror(): Integer error number to string converter.
 * @return int 
 */
int	print_error_errno(char *s1, char *s2, char *s3)
{
	print_error(s1, s2, s3, strerror(errno));
	errno = 0;
	return (ERROR);
}
