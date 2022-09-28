/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:41:13 by gsever            #+#    #+#             */
/*   Updated: 2022/09/28 15:02:16 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_run(t_base *base)
{
	base->split_count = word_count(base->input_line);
	base->array_line = pipe_split(base->input_line);
	ft_fd(base);
	ft_fork(base);
}
