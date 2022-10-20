/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:23:40 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/13 10:23:40 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer(t_base *base, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (lexer_pipe(base, str, &i) == ERROR)
			break;
		if (lexer_redir(base, str, &i) == ERROR)
			break;
		if (lexer_text(base, str, &i) == ERROR)
			break;
		if (lexer_quote(base, str, &i) == ERROR)
			break;
		while (str[i] && ft_strchr(WHITESPACES, str[i]))
			i++;
	}
	if (str[i] != '\0')
		exit_status(ENOMEM, 0);
	debug_print_str(base, "DEBUG", "print");
}