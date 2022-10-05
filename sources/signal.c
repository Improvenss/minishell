/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:38:26 by gsever            #+#    #+#             */
/*   Updated: 2022/10/05 14:09:04 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief CTRL+C -> ^C yapildiginda islemi yapildiginda, islemi kesmek
 *  ve yeni satira gecmek icin kullaniliyor.
 * 
 * @param sig 
 * @fn write()
 * @fn rl_replace_line()
 * @fn rl_on_new_line()
 * @fn rl_redisplay()
 */
void	action(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
