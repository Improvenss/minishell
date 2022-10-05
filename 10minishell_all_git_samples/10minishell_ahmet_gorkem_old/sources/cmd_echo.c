/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:36:40 by gsever            #+#    #+#             */
/*   Updated: 2022/10/04 17:48:07 by gsever           ###   ########.fr       */
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

/*char	*env_echo_writer(t_base *base, int i, int first, int l)
{
	int	o;
	int	c;
	int	count;
	int	rest;

	o = -1;
	rest = first;
	while (base->environ[++o])
	{
		c = -1;
		count = 0;
		first = rest;
		while (base->environ[o][++c])
		{
			if (base->environ[o][count] == base->array_line[i][first] \
			&& first <= l)
			{
				count++;
				first++;
			}
			if ((base->array_line[i][first] == '\0' \
			|| base->array_line[i][first] == '$')
			&& base->environ[o][count] == '='
			&& base->array_line[i][l] != '-')
			{
				return (&base->environ[o][++count]);
			}
		}
	}
	return (NULL);
}*/

int	cmd_echo_dolar(t_base *base, int i, int l)
{
	int		first;
	char	*env_name;
	int		count;
	
	if (base->array_line[i][l] == '\0')
	{
		write(1, "$", 1);
		return (l);
	}
	first = l;
	while (base->array_line[i][l] != '\0'
		&& base->array_line[i][l] != '$' && base->array_line[i][l] != '-')
		l++;
	env_name = (char *)malloc(sizeof(char) * (l - first + 2));
	l = first;
	count = 0;
	while (base->array_line[i][l] != '\0' && base->array_line[i][l] != '$' && base->array_line[i][l] != '-')
	{
		env_name[count] = base->array_line[i][l];
		l++;
		count++;
	}
	env_name[count] = '\0';
	ft_putstr_fd(env_findret(base, env_name), 1);
	return (l);
}

void	cmd_echo_print(t_base *base, int i)
{
	int	l;

	while (base->array_line[i])
	{
		l = -1;
		while (base->array_line[i][++l])
		{
			if (base->array_line[i][l] == '$')
			{
				l = cmd_echo_dolar(base, i, ++l);
				continue;
			}
			write(1, &base->array_line[i][l], 1);
		}
		if (base->array_line[i + 1])
			write(1, " ", 1);
		i++;
	}
}

int	cmd_echo(t_base *base)
{
	int		i;
	bool	new_line;

	i = 0;
	if(base->array_line[1] == NULL)
		printf("\n");
	else
	{
		new_line = true;
		while (ft_strncmp_edited(base->array_line[++i], "-n", 2))
			new_line = false;
		if (base->array_line[i] == NULL)
			printf("%c", '\0');
		else
		{
			cmd_echo_print(base, i);
			if (new_line)
				printf("\n");
		}
	}
	return (0);
}
