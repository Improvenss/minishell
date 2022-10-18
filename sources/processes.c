/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 09:13:58 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/13 09:13:58 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd *tmp;

	tmp = *lst;
	if (*lst)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*lst = new;
}

int	set_fd(int oldfd, char *path, int flags[2])
{
	int fd;

	if (access(path, F_OK) == 1 && !flags[0])
	{
		errno = 127;
		return (print_error(SHELLNAME, "No such file or directory", path, NULL));
	}
	else if (access(path, R_OK) == -1 && !flags[0])
	{
		errno = 126;
		return (print_error(SHELLNAME, "permission denied", path, NULL));
	}
	else if (access(path, W_OK) == -1 && access(path, F_OK) == 0 && flags[0])
	{
		errno = 126;
		return (print_error(SHELLNAME, "permission denied", path, NULL));
	}
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

char	*str_add(char *tmp, char *str)
{
	char *mem_1;
	char *mem_2;

	mem_1 = ft_strjoin(str, "\n");
	if (tmp == NULL)
		return (mem_1);
	mem_2 = ft_strjoin(tmp, mem_1);
	free(mem_1);
	if (tmp != NULL)
		free(tmp);
	return (mem_2);
}

char	*get_heredoc_str(char *limit)
{
	char		*str;
	char		*tmp;

	str = NULL;
	tmp = NULL;
	while (errno != 130 && !ft_strncmp_edited(str, limit, ft_strlen(limit)))
	{
		free(str);
		str = readline("> ");
		if (!str)
		{
			printf("%s (wanted `%s\')\n", "minishell: warning: here-document delimited by end-of-file", limit);
			break;
		}
		if (!ft_strncmp_edited(str, limit, ft_strlen(limit)))
			tmp = str_add(tmp, str);
	}
	free(str);
	return (tmp);
}

int	set_heredoc(char *limit)
{
	int		fd[2];
	char	*str;

	errno = 0;
	if (pipe(fd) == -1)
		return (print_error(SHELLNAME, "error creating pipe", NULL, NULL));
	str = get_heredoc_str(limit);
	if (str == NULL) //crlt+D için
		return (fd[READ_END]);
	write(fd[WRITE_END], str, ft_strlen(str));
	free(str);
	close(fd[WRITE_END]);
	if (errno == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}

void	cmd_set_fd(t_lexer *tmp, t_cmd **new)
{
	int flags[2];

	if (ft_strncmp_edited(tmp->str, ">>", 2))
	{
		flags[0] = 1;
		flags[1] = 1;
		(*new)->outfile = set_fd((*new)->outfile, tmp->next->str, flags);
	}
	else if (ft_strncmp_edited(tmp->str, ">", 1))
	{
		flags[0] = 1;
		flags[1] = 0;
		(*new)->outfile = set_fd((*new)->outfile, tmp->next->str, flags);
	}
	else if (ft_strncmp_edited(tmp->str, "<<", 2))
	{
		(*new)->infile = set_heredoc(tmp->next->str);
	}
	else if (ft_strncmp_edited(tmp->str, "<", 1))
	{
		flags[0] = 0;
		flags[1] = 0;
		(*new)->infile = set_fd((*new)->infile, tmp->next->str, flags);
	}
	if ((*new)->outfile == -1 || (*new)->infile == -1)
		errno = 1;
}

t_lexer	*cmd_node_create(t_cmd **new, t_lexer *last, int i)
{
	t_lexer *tmp;

	tmp = last;
	*new = malloc(sizeof(t_cmd));
	if (!*new)
		return (NULL);
	(*new)->full_cmd = (char **)malloc(sizeof(char *) * i + 1);
	if (!(*new)->full_cmd)
		return (NULL);
	(*new)->full_path = NULL;
	(*new)->infile = STDIN_FILENO;
	(*new)->outfile = STDOUT_FILENO;
	(*new)->next = NULL;
	tmp = last;
	i = 0;
	while (tmp && tmp->flag != TOK_PIPE)
	{
		if (tmp->flag & (TOK_TEXT | TOK_D_QUOTE | TOK_S_QUOTE))//if (tmp->flag == TOK_TEXT)
		{
			(*new)->full_cmd[i] = ft_strdup(tmp->str);
			i++;
		}
		cmd_set_fd(tmp, new);
		tmp = tmp->next;
	}
	(*new)->full_cmd[i] = NULL;
	return (tmp);
}

t_lexer	*cmd_create(t_cmd **lst, t_lexer *last)
{	
	t_lexer *tmp;
	t_cmd	*new;
	int		i;

	new = NULL;
	tmp = last;
	i = 0;
	while (tmp && tmp->flag != TOK_PIPE)
	{
		if (tmp->flag & (TOK_TEXT | TOK_D_QUOTE | TOK_S_QUOTE))
			i++;
		tmp = tmp->next;
	}
	tmp = cmd_node_create(&new, last, i);
	cmd_lstadd_back(lst, new);
	if (tmp && tmp->flag == TOK_PIPE)
		tmp = tmp->next;
	return (tmp);
}

int cmd_count(t_cmd *cmd)
{
	int i;
	t_cmd *tmp;

	i = 0;
	tmp = cmd;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	fork_init(t_base *base)
{
	int	i;

	base->cmd_count = cmd_count(base->cmd);
	if (base->cmd_count > 1)
	{
		base->fd = (int **)malloc(sizeof(int *) * (base->cmd_count + 1));
		if (base->fd == NULL)
			return (0);
		i = -1;
		while (++i < base->cmd_count)
		{
			base->fd[i] = (int *)malloc(sizeof(int) * 2);
			if (base->fd[i] == NULL)
				return (0);
			pipe(base->fd[i]);
		}
		base->pid = (int *)malloc(sizeof(int) * base->cmd_count);
		if (base->pid == NULL)
			return (0);
	}
	return (1);
}

void	ft_wait(t_base *base)
{
	int	i;

	i = -1;
	while (++i < base->cmd_count)
		waitpid(base->pid[i], &errno, 0);
}

void	fd_close(t_base *base)
{
	int	i;

	i = -1;
	while (++i < base->cmd_count)
	{
		close(base->fd[i][0]);
		close(base->fd[i][1]);
	}
}

void	fork_dup(t_base *base, int i, t_cmd *cmd)
{
	if (i > 0)
		dup2(base->fd[i - 1][cmd->infile], 0);
	if (i != base->cmd_count - 1)
		dup2(base->fd[i][cmd->outfile], 1);
}

/**
 * @brief command_exec() burada calisacak.
 * 
 * @note base->cmd_count: Pipe sayisi + 1 kadar. Bu kadar process acilacak.
 * 
 * @param base 
 * @fn fork(): Eger birden fazla pipe'miz varsa o kadar calistirilacak
 *  ve islemi bitince sonlandirilacak.
 * @fn fork_dup(): Bir onceki pipe'den(fork'tan) bilgiyi alabilmek icin.
 * @fn fd_close()
 * @fn command_exec(): Komut burada calistirilacak, eger cmd_*()'da tanimli
 *  bir komut yoksa execve()'ye gonderilip calistirilacak.
 * @fn print_error(): Eger komutumuz ve execve'miz calismazsa
 *  yazdirilacak error.
 * @fn exit()
 * @fn ft_wait()
 * @return int 
 */
int	fork_start(t_base *base)
{
	int i;
	t_cmd *tmp;

	i = -1;
	base->fd_i = -1;
	tmp = base->cmd;
	while (base->cmd_count > 1 && ++i < base->cmd_count && tmp)
	{
		base->fd_i = i;
		base->pid[i] = fork();
		if (base->pid[i] == 0)
		{
			fork_dup(base, i, tmp);
			fd_close(base);
			if (command_exec(base, tmp) == ERROR)
				print_error(SHELLNAME, NULL, NULL,
				"command_exec not working!\n");
			exit(0);
		}
		tmp = tmp->next;
	}
	if (base->cmd_count > 1)
	{
		fd_close(base);
		ft_wait(base);
	}
	if (base->cmd_count == 1)
		command_exec(base, base->cmd);
	return (0);
}

void	cmd(t_base *base)
{
	t_lexer	*tmp;

	tmp = base->lexer;
	while (tmp)
	{
		tmp = cmd_create(&base->cmd, tmp);
	}
	debug_print_cmd(base, "DEBUG", "print");
	if (fork_init(base) == 0)
	{
		print_error(SHELLNAME, "fork", NULL, "Cannot allocate memory");
		cmd_exit(base, base->cmd);
	}
	fork_start(base);
}

void	processes(t_base *base)
{
	signal(SIGINT, SIG_IGN);
	lexer(base, base->input_line);
	if (lexer_syntax(base->lexer) == ERROR)
		errno = 1;
	else
	{
		cmd(base);
	}
}
