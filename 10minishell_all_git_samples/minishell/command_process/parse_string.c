#include "../minishell.h"

void with_pipe(char *str)
{
	char **cmd;
	
	cmd = split2(str, '|', -1, -1);
	ft_pipe(cmd, char_count(str, '|', 0), -1);
	ft_free_double(cmd, -1);
}

void parse_string(char *str)
{
	char	**temp;
	t_cmd	cmd;

	temp = NULL;
	if (!ft_strlen(str))
		return ;
	if (char_count(str, '|', 0))
		with_pipe(str);
	else if (ft_strchr2(str, '>') || ft_strchr2(str, '<'))
		redirect(str);
	else
	{
		temp = split2(str, ' ', -1, -1);
		cmd.command = NULL;
		cmd.cmd = ft_strdup(temp[0]);
		add_to_list(temp, &cmd.command, 0);
		ft_free_double(temp, -1);
		get_func(cmd, -1, 0);
		lstclear(&cmd.command);
		free(cmd.cmd);
	}
}
