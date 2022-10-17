/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:52:46 by gsever            #+#    #+#             */
/*   Updated: 2022/10/17 19:34:26 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	debug_print_cmd(t_base *base, char *env_var, char *value)
{
	if (env_is_have(base, env_var, value))
	{
		t_cmd *write;
		write = base->cmd;
		while (write)
		{
			int i = 0;
			while (write->full_cmd[i])
			{
				printf("CMD->[%d]: %s\n", i, write->full_cmd[i]);
				i++;
			}
			printf("[%d]: in: %d out: %d\n",i, write->infile, write->outfile);
			write = write->next;
		}
		printf("##########################################################\n");
	}
}

void	debug_print_str(t_base *base, char *env_var, char *value)
{
	if (env_is_have(base, env_var, value))
	{
		t_lexer *tmp = base->lexer;
		while (tmp)
		{
			printf("			->: STR: %s FLAG: %d\n", tmp->str, tmp->flag);
			tmp = tmp->next;
		}
		printf("##########################################################\n");
	}
}