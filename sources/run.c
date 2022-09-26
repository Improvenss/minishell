/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:41:13 by gsever            #+#    #+#             */
/*   Updated: 2022/09/26 17:19:32 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_run(t_base *base)
{	
	base->array_line = divider(base->input_line);
	int i = 0;
	while (base->array_line[i])
	{
		printf("%d - #%s#\n", i, base->array_line[i]);
		i++;
	}
	printf("Çalışıyor.\n");
}
