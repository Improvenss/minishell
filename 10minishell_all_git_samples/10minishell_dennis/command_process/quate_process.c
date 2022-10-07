#include "../minishell.h"

int	dolar_sign(char *str)
{
	char *temp;
	int i;

	i = -1;
	temp = NULL;
	while (str[++i])
		if (str[i] != '$' && str[i] != '_' && !ft_isalpha(str[i]))
			break;
	temp = ft_substr(str, 0, i);
	if (getenv(&temp[1]) == NULL)
			return (i);
	write(1, getenv(&temp[1]), ft_strlen(getenv(&temp[1])));
	free(temp);
	return(i);
}

void print_all(char *str, int i, int quote)
{
	while (str[++i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = str[i];
		if (str[i] == '$' && quote != '\"')
			i +=  dolar_sign(&str[i]);
		else
			write(1, &str[i], 1);
	}
}
