/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:22:47 by gsever            #+#    #+#             */
/*   Updated: 2022/10/05 14:09:23 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils_split.c
 * @author Ahmet KARACA (akaraca)
 * @author Gorkem SEVER (gsever)
 * @brief 
 * @version 0.1
 * @date 2022-10-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../includes/minishell.h"

/**
 * @brief &'la adresini gondererek temizleme islemi yapiyor.
 * 
 * @param split 
 * @fn free()
 */
void	ft_free_split(char ***split)
{
	int	i;

	i = 0;
	while ((*split)[i] != NULL)
	{
		free((*split)[i]);
		(*split)[i] = NULL;
		i++;
	}
	free(*split);
	*split = NULL;
}

/**
 * @brief 2 array yapisindaki icerigini sayip uzunlugunu donduruyor.
 * 
 * @param split 
 * @return int 
 */
int	split_count(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}
