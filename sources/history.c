/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:52:30 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/06 17:52:43 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	history_empty_check(char *input_line)
{
	static char	*last_entry;
	int			i;
	int			l;

	if (ft_strcmp_edited(input_line, last_entry) == 0)
		return (0);
	free(last_entry);
	last_entry = ft_strdup(input_line);
	l = 0;
	i = 0;
	while (input_line[i])
	{
		if (input_line[i] == ' ')
			l++;
		i++;
	}
	if (i == l)
		return (0);
	return (1);
}
