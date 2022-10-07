#include "minishell.h"

char *rl_gets(char *str, const char *prompt)
{
	if (str)
		free(str);
	str = readline(prompt);
	if (!str)
	{
		write(2, "exit\n", 6);
		exit(0);
	}
	if (str && *str)
		add_history(str);
	return (str);
}

void loop(void)
{
	char *input;
	char *user;

	input = NULL;
	user = ft_strjoin2(ft_strjoin(""BGreen"", getenv("LOGNAME")), " % "X"");
	while (1)
	{
		input = rl_gets(input, user);
		parse_string(input);
	}
}

int main(void)
{
	shell_msg();
	loop();
}
