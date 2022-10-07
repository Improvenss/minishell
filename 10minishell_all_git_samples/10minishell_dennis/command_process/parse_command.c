#include "../minishell.h"

int word_count(char *str, char c, int i, int ret)
{
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && !quote_state(str, i, -1, 0))
			ret++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (ret);
}

int cut_str(char *dst, char **src, char c, int i)
{
	while (dst[++i])
		if (dst[i] == c && !quote_state(dst, i, -1, 0))
			break ;
	*src = ft_substr(dst, 0, i);
	return (i);
}

char **split2(char *str, char c, int len, int ret_index)
{
	char **ret;
	int i;

	i = 0;
	ret = malloc(sizeof(char *) * (word_count(str, c, 0, 0) + 1));
	while (++len < word_count(str, c, 0, 0))
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] != c)
			i += cut_str(&str[i], &ret[++ret_index], c, -1);
	}
	ret[++ret_index] = NULL;
	return (ret);
}
