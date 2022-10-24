/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:30:15 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/24 19:26:53 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief CTRL+C (^C) sinyalini gonderdigimizde terminaldeki echo yankisini
 *  engellemek icin kullaniyoruz.
 * 
 * termios.h'taki termios structunu kullanarak bir terminal
 * 
*@link https://stackoverflow.com/questions/42563400/hide-c-pressing-ctrl-c-in-c
*@link https://stackoverflow.com/questions/608916/ignoring-ctrl-c
 * 
 * @param echo_ctrl_character 
 * @return int 
 */
int	termios_change(bool echo_ctrl_character)
{
	struct termios	attribute;
	int				status;

	status = tcgetattr(STDOUT_FILENO, &attribute);
	if (status == -1)
		return (ERROR);
	if (echo_ctrl_character)
		attribute.c_lflag |= ECHOCTL;
	else
		attribute.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &attribute);
	if (status == -1)
		return (ERROR);
	return (0);
}

void	action_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		exit_status(130, 0);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		//rl_redisplay();
	}
}

void	action(int sig)
{
	if (sig == SIGINT)
	{
		exit_status(1, 0);
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
