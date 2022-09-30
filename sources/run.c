/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:41:13 by gsever            #+#    #+#             */
/*   Updated: 2022/09/30 14:00:29 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_run(t_base *base)
{
	base->split_count = pipe_word_count(base->input_line);
	base->input_line = delete_space(base->input_line, 0, 0, 0);
	base->pipe_line = pipe_split(base->input_line);
	int i = 0;
	while (base->pipe_line[i])
	{
		base->pipe_line[i] = delete_space(base->pipe_line[i], 0, 0 ,0);
		i++;
	}
	ft_fd(base);
	ft_fork(base);
}
