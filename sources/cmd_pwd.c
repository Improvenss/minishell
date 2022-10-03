/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:04:05 by gsever            #+#    #+#             */
/*   Updated: 2022/10/03 19:04:30 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_pwd(t_base *base)
{
	(void)*base;
	printf("%s\n", env_findret("PWD=", base));
	//printf("we are inside pwd cmd\n");
	return (0);
}
