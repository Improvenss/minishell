/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:36:40 by gsever            #+#    #+#             */
/*   Updated: 2022/10/01 22:02:16 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cmd_echo.c
 * @author Görkem SEVER (gsever)
 * @author Ahmet KARACA (akaraca)
 * 
 * @brief 'echo' komutunun kaynagi.
 * 
 * @version 0.1
 * @date 2022-10-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../includes/minishell.h"

/**
 * @brief 
 * 
 * @param base 
 * @param word 
 */
void	cmd_echo_print(t_base *base, int word)
{
	int	i;
	int	k;

	i = word;
	k = 1;
	while (ft_strncmp_edited(base->array_line[i], "-n", 2))
	{
		i++;
		k = 0;
	}
	if (base->array_line[i] == NULL	)
		printf("%c", '\0');
	else
	{
		while (base->array_line[i + 1])
			printf("%s ", base->array_line[i++]);
		printf("%s", base->array_line[i]);
		if (k == 1)
			printf("\n");
		else
			printf("%c", '\0');
	}
}

int	cmd_echo(t_base *base)
{

	if(base->array_line[1] == NULL)
		printf("\n");
	else
		cmd_echo_print(base, 1);
	printf("We are inside echo command!!\n");
	return (0);
}