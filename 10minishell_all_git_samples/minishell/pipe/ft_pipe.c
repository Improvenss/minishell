#include "../minishell.h"

void	ft_multiple_close(int **fd, int len, int i, int j)
{
	while (i < len)
	{
		if (j == 2)
		{
			j = 0;
			i++;
		}
		if (close(fd[i][j]) < 0 && i != len)
			perror("close ");
		j++;
	}
}

int		**ft_multiple_fd(int count, int i)
{
	int **fd;

	fd = malloc(sizeof(int *) * count + 1);
	while (++i <= count)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			printf("error memory allocation\n");
			return (NULL);
		}
	}
	i = -1;
	while (++i <= count)
		if (pipe(fd[i]) < 0)
			perror("pipe ");
	return (fd);
}

int		ft_fork(void)
{
	int pid;

	pid = fork();
	if (pid < 0)
	{
		perror("pid ");
		return (-1);
	}
	return(pid);
}

void	multiple_waitpid(int *pid, int count, int i)
{
	while (++i < count)
		waitpid(pid[i], NULL, 0);
}

void	ft_pipe(char **cmd, int count, int i)
{
	int	**fd;
	int	*pid;

	pid = malloc(sizeof(int) * count + 1);
	fd = ft_multiple_fd(count + 1, -1);
	while (++i <= count)
	{
		pid[i] = ft_fork();
		if (pid[i] == 0)
		{
			if  (i > 0)
				dup2(fd[i - 1][0], STDIN_FILENO);
			if (i != count)
				dup2(fd[i][1], STDOUT_FILENO);
			ft_multiple_close(fd, count + 1, 0, 0);
			parse_string(cmd[i]);
			exit(0);
		}
	}
	ft_multiple_close(fd, count + 1, 0, 0);
	multiple_waitpid(pid, count + 1, -1);
	ft_free_int(fd, count + 1, -1);
	free(pid);
}
