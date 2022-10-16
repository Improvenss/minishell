/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:23:33 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/15 15:23:33 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_exit(t_base *base, t_cmd *cmd)
{
	(void)*base;
	(void)*cmd;
	ft_putendl_fd(RED"exit"END, STDERR_FILENO);
	exit(0);
	return (0);
}
