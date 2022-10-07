/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarhan <dkarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:33:14 by dkarhan           #+#    #+#             */
/*   Updated: 2022/02/10 17:33:14 by dkarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*my_list;

	my_list = (t_list *)malloc(sizeof(t_list));
	if (!my_list)
		return (NULL);
	my_list -> content = content;
	my_list -> next = NULL;
	return (my_list);
}
