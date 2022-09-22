/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:57:07 by akaraca           #+#    #+#             */
/*   Updated: 2022/09/22 00:47:10 by gsever           ###   ########.fr       */
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
	execve()	-> Execute program,
	dup()		-> Duplicate a file descriptor(fd) -> int dup2(int oldfd);,
	dup2()		-> Duplicate a fd with -> int dup2(int oldfd, int newfd);,
	pipe()		-> Create pipe -> int pipe(int pipefd[2]);,
	isatty()	-> Tests if there is an open file. If have open any file
		return 1, not have opened file return 0. -> int isatty(int fd);,
	ttyname()	-> Get name of associated terminal (tty) from file descriptor.
		It's working if isatty() is true.
	ttyslot()	-> Find the slot of the current user's terminal in some file. */
# include <stdlib.h> /*
	free()		-> Deallocatig all allocated memory,
	exit()		-> Closing everything with atexit() and terminates program,
	getenv()	-> Get an environment variable. */
# include <stdio.h> /*
	printf()	-> A library function to send formatted output to the screen,
	perror()	-> System error messages -> void perror(const char *s);. */
# include <signal.h> /*
	signal()	-> 
	sigaction()	-> 
	sigemptyset()	-> 
	sigaddset()	-> 
	kill()		-> Close process from PID. */
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
		It can retrieve capabilities by either termcap or terminfo name. */
# include <term.h> /*
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

# define ITALIC "\e[3;37m" //stringi eğik yazar.
# define UNDERLINE "\e[4;37m" //Stringi altı çizgili yapar.
# define SELECTED "\e[7;37m" //Stringi seçilmiş şekilde yazdırır.
//(yazının arka planı koyu olur.)
# define SELECTED_2 "\e[0;40m" // stringi seçilmiş şekilde yazdırır.
//(arka plan hafif koyu olur.)
# define HIDDEN "\e[8;37m" // stringi gizli bir şekilde ekrana bastırır.
# define BLINK "\e[5;37m" // yanıp sönmeli şekilde çıktıyı verir, lakin bu özellik bizde yok :(
# define RED_BLINK "\e[1;3;5;31m"

# define SHELL_META_CHARS "|<>"
# define SHELL_QUOTE_CHARS	"'\""
# define SHELL_ESCAPE "\\"

//	COLORS BOLD--> B🟥 B🟩 B🟦
# define B_CYAN		"\033[1;36m"
# define B_BLUE		"\033[1;34m"
# define B_YELLOW	"\033[1;33m"
# define B_GREEN	"\033[1;32m"
# define B_RED		"\033[1;31m"
# define B_RESET	"\033[1m"

/* ************************************************************************** */
/* STRUCT DEFINES AREA													  	  */
/* ************************************************************************** */

/**
 * @brief Yazdigimiz komutun dogrulugunu kontrol ediyor.
 * 
 * @param first  
 * @param last
 * @param lenght
 * @param count
 * @param token
 */
typedef struct s_syntax
{
	int		first;
	int		last;
	int		lenght;
	int		count;
	char	token;
}		t_syntax;

/**
 * @brief env yapısını içerecek
 * 
 * @param data**	data[0] -> PWD,OLDPWD,HOME,_ .... data[1] 
 * 	-> /Users/akaraca/Desktop/minishell/sources,
 * 		/Users/akaraca/Desktop/minishell, /Users/akaraca ...
 * @param next*		env listesinin bir sonraki argümanını işaret ediyor.
 * @param prev*		env listesinden argüman silmek için kullandığım,
 * 	bir önceki argümanı işaret eden işaretçi.
 */
typedef struct s_env
{
	char	**data;
	struct s_env *next;
	struct s_env *prev;
}		t_env;

/**
 * @brief 
 * 
 * @param fd**			
 * @param pid*			
 * @param split_count	pipe kullanımında split edilen komut satırını tutuyor.
 * @param echo_val		echo $? <enter> için geri dönüş değeri,
 * 		0 1 127 ve 130 değerlerine sahiptir.(arttırılabilir)!
 * @param PATH**		Komut pathleri 2 boyutlu dizi olarak saklanmaktadır.
 * @param terminal_name*	Leak'i gidermek için ft_terminal_print
 * 		çıktısını her döngüde buna eşitlemeliyiz.
 * @param command_path*	ls, clear, man ... vb komutların
 * 		"/bin/..." dizinin eşitliğini tutuyor.
 * @param tmp_str*		pwd ve oldpwd eşitliğinde veri tutmak için kullanıyorum.
 * @param input_line*	realine(), geri dönüş değerini tutuyor.
 * @param array_line**	Girilen komut satırını 2 boyutlu dizede tutuyorum,
 * 		ekstra bir karakter girdisi yok.
 * @param environ**		"extern char	**environ;" hafızaya alıyorum.
 * @param env*			extern char **environ; 2 boyutlu dizisi üzerinde
 * 		düzenleme yapabilmek için list yapısı oluşturduk.
 */
typedef struct s_main
{
	int			**fd;
	int			*pid;
	int			split_count;
	int			echo_val;
	char		**PATH;
	char		*terminal_name;
	char		*command_path;
	char		*tmp_str;
	char		*input_line;
	char		**array_line;
	char		**environ;
	t_env		*env;
	t_syntax	syntax;
}		t_main;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

t_main	g_main;

int		main(void);

//exit.c
void	ft_exit(int error, char *str1, char *str2, char *str3);

// history.c
int		history_empty_check(char *str);

// init_all.c
void	init_syntax(void);

// minishell.c
void	minishell(void);

// print.c
char	*directory_name(char *path);
char	*terminal_print(void);

// run.c
void	command_run(void);

// set_argument.c
void	login_print(void);
char	*env_findret(char *env_name);
void	env_struct(char *env_arg);
void	set_argument(void);

// signal.c
void	action(int sig);

//syntax_pipe.c
int		syntax_pipe(int i);

// syntax_quote.c
void	double_quote(int i);
void	single_quote(int i);
int		syntax_quote(int i);

// syntax_redirection.c
int		syntax_heredoc(void);
int		syntax_left_right(void);

// syntax.c
int		ft_redirection(void);
int		ft_pipe(void);
int		ft_quote(void);
int		syntax(void);

// utils.c
int		look_the_quote(char *str, int i);
char 	*delete_space(char *str);

#endif