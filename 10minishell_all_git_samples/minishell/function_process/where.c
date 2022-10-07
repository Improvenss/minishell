#include "../minishell.h"

void	shell_msg()
{
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("   "RED"               ▄█████████▄              \n", 2);
	ft_putstr_fd("   "RED"            ▄███"YELLOW"█████████"RED"███▄           \n", 2);
	ft_putstr_fd("   "RED"         ███"YELLOW"███▀   ██   ▀████"RED"███        \n", 2);
	ft_putstr_fd("   "RED"      ███"YELLOW"   ▀███   ██   ███▀   "RED"███      \n", 2);
	ft_putstr_fd("   "RED"     ████"YELLOW"██   ██   ██   ██   ██"RED"████     \n", 2);
	ft_putstr_fd("   "RED"    ███"YELLOW"   ██   ██  ██  ██   ██   "RED"██     \n", 2);
	ft_putstr_fd("   "RED"    ███"YELLOW"    ██  ██  ██  ██  ██    "RED"███    \n", 2);
	ft_putstr_fd("   "RED"    ██"YELLOW" ██   ██  █  ██  █  ██   ██ "RED"██    \n", 2);
	ft_putstr_fd("   "RED"    ██"YELLOW"  ███  ██ ██ ██ ██ ██  ███  "RED"██    \n", 2);
	ft_putstr_fd("   "RED"    ██"YELLOW"    ██  ██ █ ██ █ ██  ██    "RED"██    \n", 2);
	ft_putstr_fd("   "RED"    ████▄"YELLOW"   ██ █ ██████ █ ██   "RED"▄████    \n", 2);
	ft_putstr_fd("   "RED"       ████"YELLOW"   ████████████   "RED"████       \n", 2);
	ft_putstr_fd("   "RED"          ██"YELLOW"                "RED"██          \n", 2);
	ft_putstr_fd("   "RED"          ████████▄  ▄████████          \n", 2);
	ft_putstr_fd("   "RED"                  ▀██▀                  \n"BBlack"", 2);
	ft_putstr_fd("              _       _     _          _ _ \n", 2);
	ft_putstr_fd("    _ __ ___ (_)_ __ (_)___| |__   ___| | |\n"BLUE"", 2);
	ft_putstr_fd("   | '_ ` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |\n"BBlue"", 2);
	ft_putstr_fd("   | | | | | | | | | | \\__ \\ | | |  __/ | |\n"X"", 2);
	ft_putstr_fd("   |_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|\n\n\n"X"", 2);
}

int find_path(char *path, char *cmd)
{
	struct dirent *de;
	DIR *dir;

	dir = opendir(path);
	if (dir == NULL)
	{
		printf("Could not open current directory");
		return (0);
	}
	while ((de = readdir(dir)))
	{
		if (ft_strstr(de->d_name, cmd))
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

char *where(char *cmd, int i)
{
	char **temp;
	char *ret;

	ret = NULL;
	temp = ft_split(getenv("PATH"), ':');
	while (temp[++i])
	{
		if (find_path(temp[i], cmd))
		{
			ret = ft_strdup(temp[i]);
			break ;
		}
	}
	ft_free_double(temp, -1);
	return(ret);
}
