/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarhan <dkarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:33:52 by dkarhan           #+#    #+#             */
/*   Updated: 2022/02/10 17:33:52 by dkarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*s_to_word(char *str, const char *s, int son, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		str[i] = s[son - len + i];
	str[i] = '\0';
	return (str);
}

static char	**word_to_words(char **str, char const *s, char c, int word_size)
{
	int	i;
	int	word_len;
	int	n;

	n = 0;
	i = 0;
	word_len = 0;
	while (n < word_size)
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		while (s[i] != '\0' && s[i] != c)
		{
			word_len++;
			i++;
		}
		str[n] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!str)
			return (0);
		s_to_word(str[n], s, i, word_len);
		word_len = 0;
		n++;
	}
	str[n] = 0;
	return (str);
}

static int	word_count(char const *str, char c)
{
	int	sum;
	int	i;

	i = 0;
	sum = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			while (str[i] && str[i] != c)
				i++;
			sum++;
		}
	}
	return (sum);
}

char	**ft_split(const char *s, char c)
{
	char	**words;
	int		word_size;

	if (!s)
		return (0);
	word_size = word_count(s, c);
	words = malloc(sizeof(char *) * (word_size + 1));
	if (!words)
		return (0);
	return (word_to_words(words, s, c, word_size));
}
