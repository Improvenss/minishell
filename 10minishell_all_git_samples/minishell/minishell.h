#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include "./libft/libft.h"

# define BBlack "\033[1;30m"          
# define BBlue "\033[1;34m"
# define BGreen "\033[1;32m"
# define BLUE	"\033[0;34m"
# define LB		"\033[0;36m"
# define YELLOW	"\033[0;33m"
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define RESET	"\033[0m"
# define X		"\033[m"

extern char **environ;

typedef struct s_cmd
{
	char	*cmd;
	t_list	*command;
}	t_cmd;

typedef struct s_func
{
	void	*(*func_name)(t_cmd);
}	t_func;

typedef struct s_functions
{
	t_func	func;
	char	*arg;
}	t_functions;

//-------------main process--------------//
void		loop();

//-------------built-in--------------//
void 		env(t_cmd cmd);
void 		exit_f(t_cmd cmd);
void		export(t_cmd cmd);
//void		unset(t_cmd *cmd);
void		cd(t_cmd cmd);
void		pwd(t_cmd cmd);
void		ft_echo(t_cmd cmd);
int			ft_execve(t_cmd cmd);

//-------------utils--------------//
void		multiple_waitpid(int *pid, int count, int i);
void		ft_multiple_close(int **fd, int len, int i, int j);
int			ft_fork(void);
int 		**ft_multiple_fd(int count, int i);
char		*ft_strjoin2(char *s1, char *s2);
char		*ft_read(int fd);
void		ft_pipe(char **cmd, int count, int i);
void		ft_free_double(char **pointer, int i);
char		*sequence(char *str);
char 		**split2(char *str, char c, int len, int ret_index);
int			ft_strstr(char *s1, char *s2);
char		*clear_quote(char *str, int i, int j, int len);
int			char_count(char *str, char c, int ret);
int			first_quote(char *str);
void		print_all(char *str, int i, int quote);
int			ft_isspace(char str);
void		set_funcs(t_functions *func);
void		get_func(t_cmd cmd, int i, int ret);
int			dolar_sign(char *str);
int			quote_state(char *str, int pos, int i, int quote);
int			word_count(char *str, char c, int i, int ret);
//void		single_right_redirect(char *path);
void		parse_string(char *str);
int 		redirect(char *cmd);
char		*where(char *cmd, int i);
void		ft_free_int(int **pointer, int count, int i);
int			ft_strchr2(char *s, int c);

//-----------------------------------------------------//
void	add_to_list(char **temp, t_list **cmd, int i);
void	lst_find(t_list **lst, void *data);
void	lstclear(t_list **lst);
void	shell_msg();

#endif
