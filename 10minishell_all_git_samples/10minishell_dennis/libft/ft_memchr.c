/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarhan <dkarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:33:19 by dkarhan           #+#    #+#             */
/*   Updated: 2022/02/10 17:33:19 by dkarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_dst;

	ptr_dst = (unsigned char *)s;
	while (n--)
	{		
		if (*ptr_dst == (unsigned char)c)
			return (ptr_dst);
		ptr_dst++;
	}
	return (NULL);
}
