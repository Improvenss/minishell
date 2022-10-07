/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarhan <dkarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:33:30 by dkarhan           #+#    #+#             */
/*   Updated: 2022/02/12 21:14:05 by dkarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*ptr_dst;
	char	*ptr_src;
	size_t	i;

	ptr_dst = (char *)dst;
	ptr_src = (char *)src;
	if (!ptr_dst && !ptr_src)
		return (NULL);
	i = 0;
	if (ptr_dst > ptr_src)
		while (++i <= len)
			ptr_dst[len - i] = ptr_src[len - i];
	else
		while (len-- > 0)
			*(ptr_dst++) = *(ptr_src++);
	return (dst);
}
