#include "../minishell.h"

void pwd(t_cmd cmd)
{
	char *cwd;

	cwd = NULL;
	if (cmd.command)
	{
		printf("with no options \n");
		return ;
	}
	cwd = getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	free(cwd);
}
