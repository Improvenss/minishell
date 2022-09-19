/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:05:42 by gsever            #+#    #+#             */
/*   Updated: 2022/09/19 13:39:16 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Ctrl+C, Ctrl+\ islevleri icin kullaniliyor.
 * 
 * Ctrl-C signal, yeni bir satıra geçiş yapmalı.
 * Ctrl-\ signal, hicbir sey yapmamali.
 * 
 * @param sig 
 * @fn printf()
 * @fn rl_on_new_line() 
 * @fn rl_replace_line()
 * @fn rl_redisplay()
 */
void	action(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_main.echo_val = 130;
	}
	else if (sig == 3)
		printf("%s", "\n");
}
