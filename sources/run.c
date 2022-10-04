/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:41:13 by gsever            #+#    #+#             */
/*   Updated: 2022/10/03 19:56:27 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_run(t_base *base)
{
	int	i;
	
	base->split_count = pipe_word_count(base->input_line);
	base->pipe_line = pipe_split(base->input_line);
	i = -1;
	while (base->pipe_line[++i])
		base->pipe_line[i] = delete_space(base->pipe_line[i], 0, 0 ,0);
	if (fork_init(base) == 0)
	{
		print_error(SHELL_NAME, "fork", NULL, "Cannot allocate memory");
		cmd_exit(base);
	}
	fork_start(base, -1);
}
