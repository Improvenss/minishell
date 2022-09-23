/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:18:39 by gsever            #+#    #+#             */
/*   Updated: 2022/09/23 14:36:32 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
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
	printf("This terminal PID	-> %d\n", getpid());
	printf("This terminal name	-> %s\n", ttyname(STDIN_FILENO));
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
