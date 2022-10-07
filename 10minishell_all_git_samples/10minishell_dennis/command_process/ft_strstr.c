#include "../minishell.h"

int ft_strstr(char *s1, char *s2)
{
    int i;

    i = 0;
    if (!s2)
        return (0);
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    if (i == (int)ft_strlen(s1) && ft_strlen(s1) == ft_strlen(s2))
        return (1);
    return (0);
}