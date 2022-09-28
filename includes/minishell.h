/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:43:17 by gsever            #+#    #+#             */
/*   Updated: 2022/09/28 11:53:42 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/includes/libft.h"
# include <unistd.h> /*
	write()		-> System call used to write data from the buffer
		ssize_t	write(int fd, const void *buf, size_t count);
https://man7.org/linux/man-pages/man2/write.2.html
	read()		-> Read from a file descriptor
		ssize_t read(int fd, void *buf, size_t count);
https://man7.org/linux/man-pages/man2/read.2.html
	fork()		-> Create thread from process
		pid_t fork(void);
https://man7.org/linux/man-pages/man2/fork.2.html
	access()	-> Check accessibility of a file
		int access(const char *pathname, int mode);
https://man7.org/linux/man-pages/man2/faccessat.2.html
	getcwd()	-> Get current working directory
		char *getcwd(char *buf, size_t size);
https://www.ibm.com/docs/en/i/7.4?topic=ssw_ibm_i_74/apis/getcwd.htm
	chdir()		-> Change working directory
		int	chdir(const char *path);
https://www.ibm.com/docs/en/i/7.4?topic=ssw_ibm_i_74/apis/chdir.htm
	unlink()	-> Delete a name and possibly the file it refers to
		int	unlink(const char *path);
https://shorturl.at/HKQ29
	execve()	-> Execute program
		int execve(const char *pathname, char *const argv[],
			char *const envp[]);
https://man7.org/linux/man-pages/man2/execve.2.html
	dup()		-> Duplicate a file descriptor(fd).
		int dup(int oldfd);
https://man7.org/linux/man-pages/man2/dup2.2.html
	dup2()		-> Duplicate a fd with
		int dup2(int oldfd, int newfd);
https://man7.org/linux/man-pages/man2/dup2.2.html
	pipe()		-> Create pipe
		int pipe(int pipefd[2]);
https://www.ibm.com/docs/en/i/7.5?topic=ssw_ibm_i_75/apis/pipe2.htm
	isatty()	-> Tests if there is an open file. If have open any file
			return 1, not have opened file return 0.
		int isatty(int fd);
https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-isatty-test-if-descriptor-represents-terminal
	ttyname()	-> Get name of associated terminal (tty) from file descriptor.
			It's working if isatty() is true.
		char *ttyname(int fildes);
https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-ttyname-get-name-terminal#rttty
	ttyslot()	-> Find the slot of the current user's terminal in some file.
		int ttyslot(void);
https://man7.org/linux/man-pages/man3/ttyslot.3.html
*/
# include <stdlib.h> /*
	free()		-> Deallocatig all allocated memory
		void free(void *ptr);
https://www.ibm.com/docs/en/i/7.5?topic=functions-free-release-storage-blocks
	exit()		-> Closing everything with atexit() and terminates program
		noreturn void exit(int status);
https://man7.org/linux/man-pages/man3/exit.3.html
	getenv()	-> Get an environment variable.
		char *getenv(const char *name);
https://www.ibm.com/docs/en/i/7.5?topic=ssw_ibm_i_75/apis/evgetenv.htm
https://linuxhint.com/getenv-function-usage/
*/
# include <stdio.h> /*
	printf()	-> A library function to send formatted output to the screen
		int printf(const char *restrict format, ...);
https://man7.org/linux/man-pages/man3/printf.3.html
	perror()	-> System error messages
		void perror(const char *string);
https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-perror-print-error-message
*/
# include <signal.h> /*
	signal()	-> Simplified software signal facilities.
		void (*signal(int sig, void (*func)(int)))(int);
https://linuxhint.com/signal_handlers_c_programming_language/
	sigaction()	-> 
		int sigaction(int signum, const struct sigaction *restrict act,
		struct sigaction *restrict oldact);
https://www.ibm.com/docs/en/zos/2.1.0?topic=functions-sigaction-examine-change-signal-action#rtsigac
	sigemptyset()	-> 
		int sigemptyset(sigset_t *set);
https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-sigemptyset-initialize-signal-mask-exclude-all-signals
	sigaddset()	-> 
		int sigaddset(sigset_t *set, int signal);
https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-sigaddset-add-signal-signal-mask
	kill()		-> Send Signal to Process or Group of Processes. (PID).
		int kill(pid_t pid, int sig);
https://www.ibm.com/docs/en/i/7.2?topic=ssw_ibm_i_72/apis/sigkill.htm
*/
# include <stdint.h> /*
	Type	 	Name		Num_Bytes	Num_Bits	Integer_Range
	int8_t	 ->	char			1			8		-128 to 127,
	int16_t	 ->	short			2			16		-32768 to 32767,
	int32_t	 ->	int				4			32		-2147483648 to 2147483647,
	int64_t	 ->	long long		8			64		-9.223372e+18 to 9.223372e+18
	uint8_t	 ->	unsigned char	1			8			0 to 255,
	uint16_t ->	unsigned short	2			16			0 to 65535,
	uint32_t ->	unsigned int	4			32			0 to 4294967295,
	uint64_t ->	unsigned l_l 	8			64		0 to 18446744073709551615 */
# include <string.h> /*
	malloc()	-> Allocating memory with NULL,
	strerror()	-> System error messages -> char *strerror(int errnum);,
	 */
# include <fcntl.h> /*
	open()		-> Open files and directories,
	close()		-> Delete a descriptor. */
# include <dirent.h> /*
	opendir()	-> Open a directory -> DIR *opendir(const char *name);,
	readdir()	-> Read a directory -> struct dirent *readdir(DIR *dirp);,
	closedir()	-> Close a directory -> int closedir(DIR *dirp);. */
# include <termios.h> /*
	tcsetattr()	-> Set the parameters associated with the terminal,
	tcgetattr()	-> Get the parameters associated with the terminal. */
# include <curses.h> /*
	tgetent()	-> Direct curses interface to the terminfo capability database,
		Routine loads the entry for name. It returns 1 on success, 0 if there 
		is no such entry, and -1 if the terminfo database could not be found. 
		The emulation ignores the buffer pointer bp.
	tgetflag()	-> Routine gets the boolean entry for id,
	tgetnum()	-> Routine gets the numeric entry for id,
	tgetstr()	-> Routine returns the string entry for id. 
		Use tputs() to output the returned string,
	tgoto()		-> Routine instantiates the parameters into the given capability. 
		The output from this routine is to be passed to tputs(),
	tputs()		-> Routine is described on the curs_terminfo() manual page. 
		It can retrieve capabilities by either termcap or terminfo name.
*/
# include <sys/wait.h> /*
	wait()		-> 
	waitpid()	->
	wait3()		->
	wait4()		->  */
# include <sys/stat.h> /*
	stat()		-> Get file status,
	lstat()		-> Get file status,
	fstat()		-> Get file status, */
# include <sys/ioctl.h> /*
	ioctl()		-> Control device. */
# include <readline/readline.h> /* 
	readline()	->
	rl_clear_history()	->
	rl_on_new_line()	->
	rl_replace_line()	->
	rl_redisplay()	->
 */
# include <readline/history.h> /*
	add_history()	-> 
	*/
# include <pthread.h> /*
	*/
// # include <term.h> /*
// 	*/

//	COLORS --> 🟥 🟩 🟦
# define BLACK	"\e[0;30m"
# define RED	"\e[0;31m"
# define GREEN	"\e[0;32m"
# define YELLOW	"\e[0;33m"
# define BLUE	"\e[0;34m"
# define PURPLE	"\e[0;35m"
# define CYAN	"\e[0;36m"
# define WHITE	"\e[0;37m"
# define END	"\e[m"
# define RESET	"\033[0m"

//	COLORS BOLD--> B🟥 B🟩 B🟦
# define B_CYAN		"\033[1;36m"
# define B_BLUE		"\033[1;34m"
# define B_YELLOW	"\033[1;33m"
# define B_GREEN	"\033[1;32m"
# define B_RED		"\033[1;31m"
# define B_RESET	"\033[1m"

# define CMD_CLEAR	"\e[1;1H\e[2J"

//note: terminal isminin basina/sonuna renk kodlarini eklersek ust uste biniyor
# define T_NAME		"$> "

/* ************************************************************************** */
/* STRUCT DEFINES AREA													  	  */
/* ************************************************************************** */

// typedef struct s_base	t_base;
// typedef struct s_syntax	t_syntax;

// typedef struct s_syntax
// {
// 	t_base	*base;
// 	char	token;
// 	int		first;
// 	int		last;
// 	int		lenght;
// 	int		count;
// }		t_syntax;

/**
 * @brief Main structure for project.
 * 
 * @param input_line* Terminalimize girdigimiz satirlari aliyor.
 * @param
 */
typedef struct s_base
{
	char	syntax_token;
	int		syntax_first;
	int		syntax_last;
	int		syntax_lenght;
	int		syntax_count;


	int		*pid;
	int		**fd;
	int		split_count;
	char	**array_line;
	char	*input_line;
	char	**PATH;
	char	**environ;
}		t_base;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// action.c
void	action(int sig);

// history.c
int		history_empty_check(char *str);

// init_all.c
void	init_syntax(t_base *base);

// minishell.c
char	*env_findret(char *env_name, t_base *base);
void	set_argument(t_base *base);
void	minishell(void);

// pipe_split.c
size_t	word_count(char *s);
char	*alloc(char *s);
char	**pipe_split(char *s);

// run.c
char	*ft_path(char **path, char *tmp);
void	ft_fork(t_base *base);
void	command_run(t_base *base);

// syntax_ampersand.c
int		ampersand(t_base *base);

// syntax_brackets.c
int		syntax_brackets_near_reverse(t_base *base);
int		syntax_brackets_near(t_base *base);
int		syntax_brackets(t_base *base, int i);
int		brackets(t_base *base);

// syntax_pipe.c
int		syntax_pipe_first_half(t_base *base, int i);
int		syntax_pipe_last_half(t_base *base, int i);
int 	syntax_pipe(t_base *base, int i);
int		the_pipe(t_base *base);

// syntax_quote.c
void	single_double_quote(t_base *base, int i, char c);
int		syntax_quote(t_base *base, int i);
int		quote(t_base *base);

// syntax_ redirection.c
int		syntax_left_right(t_base *base, int i);
int		redirection(t_base *base);

// syntax.c
int		white_space(t_base *base);
int		syntax(t_base *base);

// utils.c
int		look_the_quote(char *str, int i);
char	*delete_space(char *str, int i, int k, int l);

#endif