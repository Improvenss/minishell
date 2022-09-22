/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:18:39 by gsever            #+#    #+#             */
/*   Updated: 2022/09/21 13:39:09 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * @brief 
 * 
 * @fn signal()
 * @fn terminal_print()
 * @fn readline() Ctrl+D bastigimizda readline (NULL) donduruyor.
 * 	NULL dondurdugunde de 1.if'te programi kapatmak icin kullaniliyor.
 * @fn ft_exit()
 * @fn history_empty_check() Boş girilen satırları atlamak için.
 * 	Ard arda giriş gerçekleşmiş ise yok sayılıyor.
 * @fn add_history()
 */
void	minishell(void)
{
	set_argument();
	while (1)
	{
		signal(SIGINT, action);
		signal(SIGQUIT, action);
		g_main.terminal_name = terminal_print();
		g_main.input_line = readline(g_main.terminal_name);
		if (!g_main.input_line)
			ft_exit(-1, "exit\n", "\0", "\0");
		if (history_empty_check(g_main.input_line))
			add_history(g_main.input_line);
		if (syntax())
			command_run();
		free(g_main.input_line);
		free(g_main.terminal_name);
		//system("leaks minishell");
	}
}
