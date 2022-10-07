#include "../minishell.h"

void ft_free_double(char **pointer, int i)
{
	if (!pointer || !pointer)
		return;
	while (pointer[++i])
		free(pointer[i]);
	free(pointer);
}

void ft_free_int(int **pointer, int count, int i)
{
	while (++i <= count)
		free(pointer[i]);
	free(pointer);
}
