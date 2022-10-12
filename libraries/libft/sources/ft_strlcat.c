/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:37:02 by gsever            #+#    #+#             */
/*   Updated: 2022/10/12 16:28:12 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
//birlestirip lengtini donduruyor
size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	unsigned int	c;
	unsigned int	d;

	if (size <= ft_strlen(dest))
		return (size + ft_strlen(src));
	c = ft_strlen(dest);
	d = 0;
	while (src[d] != '\0' && c + 1 < size)
	{
		dest[c] = src[d];
		c++;
		d++;
	}
	dest[c] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[d]));
}
/*
size_t degiskenlerini yazdırmanın dogru yolu “%zu” kullanmaktır.
“%zu” biciminde, z bir uzunluk degistiricidir
ve u, isaretsiz tur anlamına gelir.
*/
/*
#include <stdio.h>
int	main()
{
	char b[] = "gorkem";
	char a[] = "se";

	printf("onceki a: %s, b: %s\n", a, b);
	printf("ft_:%zu\n", ft_strlcat(a, b, 1));
	printf("sonraki a: %s, b: %s\n", a, b);
	printf("a -> %s b -> %s\n", a, b);
}
*/