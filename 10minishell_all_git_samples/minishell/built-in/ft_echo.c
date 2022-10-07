#include "../minishell.h"

int check_option(t_list **lst)
{
	if (ft_strstr("-n", (*lst)->content))
	{
		lst_find(lst, "-n");
		return (1);
	}
	return (0);
}

void ft_echo(t_cmd cmd)
{
	int i;
	int new_line;

	i = 0;
	if (cmd.command)
		new_line = check_option(&cmd.command);
	if (!cmd.command)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	while (cmd.command)
	{
		cmd.command->content = clear_quote(cmd.command->content, -1, 0, ft_strlen(cmd.command->content));
		print_all(cmd.command->content, -1, 0);
		if (cmd.command->next != NULL)
			write(STDOUT_FILENO, " ", 1);
		cmd.command = cmd.command->next;
	}
}
