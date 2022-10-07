#include "../minishell.h"

void lst_find(t_list **lst, void *data)
{
	if (!*lst)
		return;
	while (*lst)
	{
		if (!ft_strstr((*lst)->content, data))
			break;
		(*lst) = (*lst)->next;
	}
}

void	add_to_list(char **temp, t_list **cmd, int i)
{
	while (temp[++i])
		ft_lstadd_back(cmd, ft_lstnew(ft_strdup(temp[i])));
}

void	lstclear(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst);
		(*lst) = (*lst)->next;
		free(tmp->content);
		free(tmp);
	}
}