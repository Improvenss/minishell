/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:48:48 by gsever            #+#    #+#             */
/*   Updated: 2022/10/04 12:54:15 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_env(t_base *base)
{
	int	i;
	
	i = -1;
	while (base->environ[++i])
		printf("%s\n", base->environ[i]);
	return (0);
}
