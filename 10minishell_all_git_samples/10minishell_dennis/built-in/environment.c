#include "../minishell.h"

static int where_env(char *s2)
{
	int i;
	char **temp;
	char **env;

	i = 0;
	temp = split2(s2, '=', -1, -1);
	while (environ[i])
	{
		env = split2(environ[i], '=', -1, -1);
		if (ft_strstr(env[0], temp[0]))
		{
			ft_free_double(env, -1);
			break;
		}
		ft_free_double(env, -1);
		i++;
	}
	ft_free_double(temp, -1);
	return (i);
}

void env(t_cmd cmd)
{
	int i;

	i = 0;
	if (cmd.command)
	{
		write(STDOUT_FILENO, "with no options\n", 16);
		return;
	}
	while (environ[i])
		printf("%s\n", environ[i++]);
}

static int is_alnum(char *str, int i)
{
	while (str[++i])
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	return (1);
}

int check_env_arg(t_cmd cmd)
{
	char **arg;

	arg = split2(cmd.command->content, '=', -1, -1);
	if (!ft_strchr2(cmd.command->content, '=') || !arg[1] || !is_alnum(arg[0], -1))
	{
		printf("'%s' not a valid identifier\n", cmd.command->content);
		return (0);
	}
	ft_free_double(arg, -1);
	return (1);
}

void export(t_cmd cmd)
{
	int count;
	int arg_index;

	if (!cmd.command)
	{
		env(cmd);
		return ;
	}
	if (!check_env_arg(cmd))
		return;
	count = 0;
	while (environ[count])
		count++;
	while (cmd.command)
	{
		arg_index = where_env(cmd.command->content);
		if (arg_index == count)
		{
			environ[count++] = ft_strdup(cmd.command->content);
			environ[count] = NULL;
		}
		else
			environ[arg_index] = ft_strdup(cmd.command->content);
		cmd.command = cmd.command->next;
	}
}
