/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:19:30 by gsever            #+#    #+#             */
/*   Updated: 2022/10/06 16:54:11 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**g_env = NULL;

/**
 * @brief Main.
 * 
 * @fn signal()
 * @fn env_init()
 * @fn action()
 * @fn get_input()
 * @fn isatty()
 * @fn ft_putendl_fd()
 * @fn process_input()
 * @fn rl_clear_history()
 * @fn ft_free_split()
 * @fn exit()
 * @fn exec_exit_status_get()
 * 
 * @return int 
 */
int	main(void)
{
	char	*input;

	input = NULL;
	signal(SIGQUIT, SIG_IGN);
	if (env_init() == ERROR)
		return (EXIT_FAILURE);
	while (1)
	{
		signal(SIGINT, action);
		input = get_input(input);
		if (input == NULL)
		{
			if (isatty(STDERR_FILENO))
				ft_putendl_fd(RED"exit"END, STDERR_FILENO);
			break ;
		}
		process_input(input);
	}
	rl_clear_history();
	if (g_env)
		ft_free_split(&g_env);
	exit(exec_exit_status_get());
}
