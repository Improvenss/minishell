/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarhan <dkarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:35:01 by dkarhan           #+#    #+#             */
/*   Updated: 2022/02/10 17:32:54 by dkarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*to_str(char *s, int basamak_s, int n, int sayi)
{
	int	rakam;

	if (n < 0)
		sayi = 1;
	s[basamak_s] = '\0';
	while (basamak_s > 0)
	{
		basamak_s--;
		rakam = n % 10;
		n /= 10;
		s[basamak_s] = rakam + '0';
		if (sayi == 1)
			s[0] = '-';
	}
	return (s);
}

char	*ctrl(void)
{
	return (ft_strdup("-2147483648"));
}

char	*ft_itoa(int n)
{
	char	*s;
	int		basamak_s;
	int		sayi;

	if (n == -2147483648)
		return (ctrl());
	sayi = n;
	basamak_s = 0;
	if (!n)
		basamak_s = 1;
	while (sayi != 0)
	{
		basamak_s++;
		sayi /= 10;
	}
	if (n < 0)
	{
		basamak_s++;
		sayi = 1;
		n *= -1;
	}
	s = (char *)malloc(sizeof(char) * basamak_s + 1);
	if (!s)
		return (NULL);
	return (to_str(s, basamak_s, n, sayi));
}
