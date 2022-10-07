#include "../minishell.h"

static char *to_lower_str(char *str, int i)
{
	char *ret;

	if (!str)
		return (str);
	while (str[++i])
		str[i] = ft_tolower(str[i]);
	ret = ft_strdup(str);
	free(str);
	return (ret);
}

void set_funcs(t_functions *func)
{
	func[0] = (t_functions){{(void *)pwd}, "pwd"};
	func[1] = (t_functions){{(void *)cd}, "cd"};
	func[2] = (t_functions){{(void *)exit_f}, "exit"};
	func[3] = (t_functions){{(void *)env}, "env"};
	func[4] = (t_functions){{(void *)export}, "export"};
	//func[5] = (t_functions){{(void *)unset}, "unset"};
	func[5] = (t_functions){{(void *)ft_echo}, "echo"};
	func[6] = (t_functions){{NULL}, NULL};
}

void get_func(t_cmd cmd, int i, int ret)
{
	char *command;
	t_functions function[7];

	set_funcs(function);
	command = to_lower_str(ft_strtrim(cmd.cmd, " "), -1);
	while (function[++i].arg != NULL)
	{
		if (ft_strstr(function[i].arg, command))
		{
			function[i].func.func_name(cmd);
			ret = 1;
			break;
		}
	}
	free(command);
	if (ret == 0)
		ft_execve(cmd);
}
