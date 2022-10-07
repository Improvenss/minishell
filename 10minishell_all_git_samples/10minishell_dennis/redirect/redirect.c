#include "../minishell.h"

int is_exist_file(char *path)
{
	return (access(path, F_OK) == -1);
}

int open_file(char *path)
{
	int fd;

	if (!path)
		return (-1);
	if (!is_exist_file(path))
		fd = open(path, O_RDWR | O_CREAT);
	else
		fd = open(path, O_APPEND | O_RDWR);
	if (fd == -1)
	{
		perror("asd2");
		return (0);
	}
	return (fd);
}

void clear_file(char *path)
{
	int	fd;

	fd = open(path, O_TRUNC);
	if (fd < 0)
		perror("");
	close(fd);
}

int red_count(char *str, int i, int ret)
{
	while (str[i])
	{
		while (str[i] && (str[i] == '<' || str[i] == '>'))
			i++;
		if (str[i] && !quote_state(str, i, -1, 0))
			ret++;
		while (str[i] && (str[i] != '<' && str[i] != '>'))
			i++;
	}
	return (ret);
}

int cut_red(char *dst, char **src, int i)
{
	while (dst[++i])
		if ((dst[i] == '<' || dst[i] == '>') && !quote_state(dst, i, -1, 0))
			break;
	*src = ft_substr(dst, 0, i);
	return (i);
}

char **redirect_split(char *str, int i, int ret_index, int len)
{
	char **ret;

	ret = malloc(sizeof(char *) * (red_count(str, 0, 0) + 1));
	while (++len < red_count(str, 0, 0))
	{
		while (str[i] && (str[i] == '<' || str[i] == '>'))
			i++;
		if (str[i] != '<' && str[i] != '>')
			i += cut_red(&str[i], &ret[++ret_index], -1);
	}
	ret[++ret_index] = NULL;
	return (ret);
}

static char **join_redirect(char **cmd, int i, int j)
{
	char **temp;

	while (cmd[++i])
	{
		j = 0;
		temp = split2(cmd[i], ' ', -1, -1);
		while (temp[++j])
		{
			cmd[0] = ft_strjoin(cmd[0], " ");
			cmd[0] = ft_strjoin(cmd[0], temp[j]);
			free(cmd[i]);
			cmd[i] = ft_strdup(temp[0]);
		}
		ft_free_double(temp, -1);
	}
	return (cmd);
}

void right_redirect(char *file)
{
	int	fd;

	fd = open_file(file);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void single_right_redirect(char *file)
{
	char *temp;

	temp = ft_strtrim(file, " ");
	if (is_exist_file(temp))
		clear_file(temp);
	right_redirect(temp);
	free(temp);
}

void double_right_redirect(char *file)
{
	char	*temp;

	temp = ft_strtrim(file, " ");
	right_redirect(temp);
}

void singel_left_redirect(char *file)
{
	int fd;
	char *temp;

	temp = ft_strtrim(file, " ");
	fd = open(temp, O_RDONLY);
	if (fd < 0)
		perror(file);
	free(temp);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

char **redirect_delimiter(char *cmd, int i, int len, int count)
{
	char	**str;
	int		j;

	str = malloc(sizeof(char *) * red_count(cmd, 0, 0));
	while (++len < red_count(cmd, 0, 0))
	{
		while (cmd[i] && (cmd[i] != '<' && cmd[i] != '>'))
			i++;
		j = i;
		while (cmd[j] && (cmd[j] == '>' || cmd[j] == '<'))
			j++;
		if (cmd[i] == '>' || cmd[i] == '<')
			str[++count] = ft_substr(cmd, i, j - i);
		i = j;
	}
	str[++count] = NULL;
	return (str);
}

void	double_left_redirect(char *eof)
{
	char	*str;
	char	*input;

	str = NULL;
	while (1)
	{
		input = readline(">");
		if (!ft_strncmp(input, eof, ft_strlen(eof)))
			break ;
		else
		{
			str = ft_strjoin2(str, input);
			str = ft_strjoin2(str, "\n");
		}
		free(input);
	}
	ft_putstr_fd(str, 1);
	dup2(STDIN_FILENO, STDOUT_FILENO);
}

int choose_redirect(char **command, char **delimeter, int i)
{
	while (delimeter[++i])
	{
		if (ft_strstr(delimeter[i], ">"))
			single_right_redirect(command[i]);
		else if (ft_strstr(delimeter[i], ">>"))
			double_right_redirect(command[i++]);
		else if (ft_strstr(delimeter[i], "<"))
			singel_left_redirect(command[i]);
		else if (ft_strstr(delimeter[i], "<<"))
			double_left_redirect(command[i++]);
	}
	return (0);
}

int redirect(char *cmd)
{
	char **tmp;
	char **delimeter;
	int pid;

	tmp = redirect_split(cmd, 0, -1, -1);
	tmp = join_redirect(tmp, 0, 0);
	delimeter = redirect_delimiter(cmd, 0, -1, -1);
	pid = fork();
	if (pid == 0)
	{
		choose_redirect(&tmp[1], delimeter, -1);
		parse_string(tmp[0]);
		exit(0);
	}
	wait(NULL);
	ft_free_double(tmp, -1);
	ft_free_double(delimeter, -1);
	return (0);
}
