/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:22:21 by gsever            #+#    #+#             */
/*   Updated: 2022/10/03 14:43:57 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_exit(t_base *base)
{
	int	exit_num;

	(void)*base;
	exit_num = INT_MAX;
	ft_putendl_fd(RED"exit"END, STDERR_FILENO);
	exit(0);
	return (0);
}
