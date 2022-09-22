/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:19:43 by gsever            #+#    #+#             */
/*   Updated: 2022/09/19 17:48:29 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Renkli, sekilli sukullu error falan yazsin diye.
 * 
 * @param error 
 * @param str1 
 * @param str2 
 * @param str3 
 * @fn printf()
 * @fn exit()
 */
void	ft_exit(int error, char *str1, char *str2, char *str3)
{
	if (str1 == NULL)
		printf("%s", "\0");
	else
		printf(RED"%s%s%s"END, str1, str2, str3);
	if (error < 0)
		exit(0);
}
