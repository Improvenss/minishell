#include "../minishell.h"

void cd(t_cmd cmd)
{
	if (cmd.command != NULL && ft_strchr2(cmd.command->content, '$'))
		cmd.command->content = sequence(cmd.command->content); //******************buna bak
	if (cmd.command == NULL)
		chdir(getenv("HOME"));
	else
	{
		cmd.command->content = clear_quote(cmd.command->content, -1, 0, ft_strlen(cmd.command->content));
		if (chdir(cmd.command->content) < 0)
			perror("");
	}
}
