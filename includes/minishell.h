/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:43:17 by gsever            #+#    #+#             */
/*   Updated: 2022/10/12 14:58:59 by gsever           ###   ########.fr       */
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
	malloc()	-> Allocating memory with NULL
		void *malloc(size_t size);
https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-malloc-reserve-storage-block
	strerror()	-> System error messages; Writing int errno's string value.
		char *strerror(int errnum);
https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-strerror-get-pointer-runtime-error-message
*/
# include <fcntl.h> /* -File control-
	open()		-> Open or Create a file for reading or writing.
		int open(const char *path, int oflag, . . .);
https://www.ibm.com/docs/en/i/7.5?topic=ssw_ibm_i_75/apis/open.htm
	close()		-> Close File or Socket descriptor.
		int close(int fd);
https://www.ibm.com/docs/en/i/7.5?topic=ssw_ibm_i_75/apis/close.htm
*/
# include <dirent.h> /* -POSIX directory access functions-
	opendir()	-> Opens a directory so that it can be
 read with readdir() or __readdir2().
		DIR *opendir(const char *dirname);
https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-opendir-open-directory#rtoped
	readdir()	-> Returns a pointer to a dirent structure describing
 the next directory entry in the directory stream associated with dir.
		struct dirent *readdir(DIR *dir);
https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-readdir-read-entry-from-directory
	closedir()	-> Closes the directory indicated by dir.
 It frees the buffer that readdir() uses when reading the directory stream.
		int closedir(DIR *dir);
https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-closedir-close-directory
*/
# include <termios.h> /* ?-General terminal line discipline-
	tcsetattr()	-> Set the parameters associated with the terminal
		int tcsetattr(int fildes, int optional_actions,
		const struct termios *termios_p);
https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-tcsetattr-set-attributes-terminal
	tcgetattr()	-> Get the parameters associated with the terminal.
		int tcsetattr(int fd, int when, const struct termios *termptr);
https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-tcsetattr-set-attributes-terminal
*/
# include <curses.h> /* -Definitions for screen handling
 and optimization functions-
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
		int fputs(const char *string, FILE *stream);
https://www.ibm.com/docs/en/i/7.5?topic=functions-fputs-write-string#fputs
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
# include <pthread.h>
# include <errno.h>

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
# define SHELLNAME	"minishell"

# define ERROR				-1
# define WHITESPACES		" \t\n"
# define QUOTE_MARKS		"\'\""

# define ERR_SYNTAX			"syntax error"
# define ERR_SYNTAX_EXIT	2

# define ERR_UNO_BRACKET	"unopened brackets"
# define ERR_UNC_BRACKET	"unclosed brackets"
# define ERR_EMPTY_BRACKET	"empty brackets"
# define ERR_REDIR			"invalid redirection"
# define ERR_QUOTE			"unclosed quotation mark"
# define ERR_LIST			"incomplete command list"
# define ERR_MISS_OP		"missing operator"
# define ERR_PIPE			"incomplete pipe"

# define CMD_SCMD			1

# define CMD_AND			2
# define CMD_OR				4
# define CMD_PIPE			8

# define CMD_O_BRACKET		16
# define CMD_C_BRACKET		32

# define CMD_PIPELINE		64
# define CMD_GROUP			128

# define CMD_L_SCMD			256
# define CMD_L_CMD			512

# define TOK_TEXT			1
# define TOK_S_QUOTE		2
# define TOK_D_QUOTE		4
# define TOK_REDIR_FILE		8
# define TOK_CONNECTED		16
# define TOK_BIN_OP			32
# define TOK_PIPE			64
# define TOK_O_BRACKET		128
# define TOK_C_BRACKET		256
# define TOK_REDIR			512
# define TOK_HEREDOC		1024
# define TOK_WILDCARD		2048

// REDIR_TYPES
# define REDIR_OUT		1
# define REDIR_OUT_APP	2
# define REDIR_IN		3
# define REDIR_HEREDOC	4

// REDIR_FDs
# define REDIR_FILE		0
# define REDIR_NUM		1

/* ************************************************************************** */
/* STRUCT DEFINES AREA													  	  */
/* ************************************************************************** */

typedef struct s_base	t_base;

/**
 * @brief Debuging'de list yazdirma islemi icin numara sirasi tutucu.
 */
typedef enum s_state
{
	LEXER,
	PARSER,
	EXPANDER,
	EXECUTOR
}		t_state;

// static const t_cmds	g_cmds[] = {
// 	{"echo", cmd_echo},
// 	{"cd", cmd_cd},
// 	{"pwd", cmd_pwd},
// 	{"unset", cmd_unset},
// 	{"export", cmd_export},
// 	{"env", cmd_env},
// 	{"exit", cmd_exit},
// 	{NULL, NULL},
// };

/**
 * @brief command'lar icin.
 * @param name*
 * @param (func*)(base*)
 */
typedef struct s_cmds
{
	char	*name;
	int		(*func)(t_base *base);
}		t_cmds;

typedef struct s_lexer
{
	int		flag;
	char	*str;
	struct	s_lexer *next;
}		t_lexer;

// typedef	struct	s_redir
// {
// 	int		flag;
// 	char	*str;
// 	struct	s_redir *next;
// }		t_redir;

// typedef struct s_argv
// {	
// 	int		flag;
// 	char	*str;
// 	struct	s_argv *next;
// }		t_argv;

typedef struct s_parser t_parser;

typedef struct s_parser
{
	int		type;
	// t_redir	*redir;
	// t_argv	*argv;
	t_parser	*element;
	t_lexer	*redir;
	t_lexer	*argv;
	struct	s_parser *next;
}		t_parser;

typedef struct s_env
{
	t_base	*base;
	char	**data;
	struct	s_env	*next;
	struct	s_env	*prev;
}		t_env;

typedef struct s_base
{
	int			exit_status;
	char		*input_line;
	char		**PATH;
	t_env		*env;
	t_lexer		*lexer;
	t_parser	*parser;
	t_cmds		cmds[3];
}		t_base;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// cmd_cd.c
int		cmd_cd(t_base *base);

// cmd_echo.c
int		cmd_echo(t_base *base);

// commands.c
void	cmd_init(t_base *base);
// int		command_find_arr(t_base *base)
int		command_find(t_base *base);
int		command_exec(t_base *base);

// debuging.c
// void	print_all_list(t_base *base);

// error.c
int		print_error(char *s1, char *s2, char *s3, char *message);
int		print_error_errno(char *s1, char *s2, char *s3);

// exec_recursive.c
// int	exec_recursive(t_base *base)

// heredoc_parser.c
int		parser_heredoc(t_lexer *lexer);

// history.c
int		history_empty_check(char *input_line);

// lexer_syntax.c
int		redir_mark_files(t_lexer *lexer);
int		lexer_syntax(t_lexer *lexer);

// lexer.c
char	*token_to_str(t_lexer *lexer);
void	lexer(t_base *base, char *str);

// main.c
int		main(int argc, char **argv, char **environ);

// minishell.c
void	minishell(t_base *base);

// parser.c
// int			parser_scmd_set(t_parser *new, t_lexer *lexer);
// t_parser	*parser_cmd_create(t_base *base, int type);
// int			parser_cmd_type(t_lexer *lexer);
// int			parser_cmd(t_base *base);
int		parser(t_base *base);

// redir.c
// void	argv_lstadd(t_argv **redir, t_lexer *new);
// void	redir_lstadd(t_redir **redir, t_lexer *new);
int		redir_type(char *redir);

// signal.c
void	signal_ctrl_heredoc(int sig);
void	action(int sig);

// utils_env.c
void	set_env(t_base *base, char *env_name, char *new_str);
char	*env_findret(t_base *base, char *env_name);
int		env_struct(t_base *base, char *new_arg);

// utils_str.c
char	*str_append_str(char *str, char *append);
char	*str_append_chr(char *str, char append);

int exec_recursive(t_base *base, bool);
#endif
