#include "../minishell.h"

int	quote_state(char *str, int pos, int i, int quote)
{
	int ret;

	ret = 0;
	while (str[++i] && i < pos)
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = str[i];
		if (quote == str[i] && ret == 0)
			ret = 1;
		else if (quote == str[i] && ret == 1)
			ret = 0;
	}
	return(ret);
}

int first_quote(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if ((str[i] == '\'' || str[i] == '\"'))
			return (str[i]);
	return (0);
}

int char_count(char *str, char c, int ret)
{
	while (*str && str != NULL)
		if (*str++ == c)
			ret++;
	return (ret);
}

char *clear_quote(char *str, int i, int j, int len)
{
	char *ret;
	int quote_len;

	quote_len = char_count(str, 34, 0) + char_count(str, 39, 0);
	ret = (char *)ft_calloc(sizeof(char), (len - quote_len) + 1);
	while (str[++i])
	{
		if (str[i] == first_quote(str))
			i++;
		ret[j++] = str[i];
	}
	free(str);
	return (ret);
}