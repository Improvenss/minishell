/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarhan <dkarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:26:41 by dkarhan           #+#    #+#             */
/*   Updated: 2022/02/12 22:12:42 by dkarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	kontrol(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*son(char const *s1, size_t start, size_t end)
{
	char	*s2;
	size_t	i;

	i = 0;
	s2 = malloc(end - start + 2);
	if (!s2)
		return (NULL);
	while (start <= end)
	{
		s2[i] = s1[start];
		start++;
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	i = 0;
	end = 0;
	while (kontrol(s1[i], set))
		i++;
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	start = i;
	i = ft_strlen(s1) - 1;
	while (kontrol(s1[i], set))
		i--;
	end = i;
	return (son(s1, start, end));
}
