/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:51:38 by gsever            #+#    #+#             */
/*   Updated: 2022/09/28 13:22:49 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file history.c
 * @author Gorkem SEVER (gsever)
 * @brief 
 * @version 0.1
 * @date 2022-09-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../includes/minishell.h"

/**
 * @brief 
 * 
 * > Komut satırına sadece <enter> veya "    " <enter> girdilerinin history
 * 	kayıt edilmesini önlemek için.
 * > static olma durumu; sürekli olarak girilen(arka arkaya) komutun
 * 	hafızaya alınmasına engel oluyor.
 * @param str 
 * @fn ft_strcmp_edited() Arka arkaya girdiyi engelliyor.
 * @fn free() Yeni girdiyi hafıza almadan önce, 2 adım önce girilen
 * 	girdinin hafızadan temizlenmesi gerekiyor.
 * @fn ft_strdup()
 * @return int 
 */
int	history_empty_check(char *str)
{
	static char	*last_entry;
	int			i;
	int			l;

	if (ft_strcmp_edited(str, last_entry) == 0)
		return (0);
	free(last_entry);
	last_entry = ft_strdup(str);
	l = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			l++;
		i++;
	}
	if (i == l)
		return (0);
	return (1);
}
