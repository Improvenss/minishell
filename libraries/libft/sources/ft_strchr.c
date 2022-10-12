/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:36:42 by gsever            #+#    #+#             */
/*   Updated: 2022/10/12 15:17:21 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/**
 * @brief String icinde char ariyoruz, buldugumuzda adresini donduruyoruz.
 * 
 * INT olarak aramak istedigimiz karakteri char'a cevirir ve
 *  buldugu anda, aradigimiz karakter dahil olmak uzere devamini dondurur.
 * NOT: Pointer'ini return ettigimizde, kendisi de dahil olmak uzere
 * devamini dondurmus oluruz.
 * 
 * @param s char * -> string
 * @param c char -> char
 * @return char* 
 */
char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
/*
int	main()
{
	char a[] = "gorkem";
	
	printf("ft_:%s", ft_strchr(a, 'r'));
}
*/