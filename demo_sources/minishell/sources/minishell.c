/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:57:07 by akaraca           #+#    #+#             */
/*   Updated: 2022/09/19 12:01:50 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

t_main	g_main;
/*
// gcc minishell.c ../includes/minishell.h -lreadline && ./a.out
// gcc -Wall -Werror -Wextra minishell.c ../includes/minishell.h  -lreadline -o minishell && ./minishell
// gcc minishell.c ../includes/minishell.h -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include && ./a.out

//brew goinfire'a kurulu ise; gcc minishell.c -L/goinfre/homebrew/opt/readline/lib -I/goinfre/homebrew/opt/readline/include -lreadline && ./a.out
//brew dosyalarını alt dizinde çalıştırmak istiyorsan; gcc minishell.c -L../includes/readline/lib -I../includes/readline/include -lreadline && ./a.out //mac'de kullanmak readline kütüphanesi sil yeniden kur(zip).
*/

//-----Functions Must be removed-------//
//ft_strncmp
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	counter;

	if (n == 0)
		return (0);
	counter = 0;
	while (counter < (n - 1) && s1[counter] && s2[counter])
	{
		if (s1[counter] != s2[counter])
			break ;
		counter++;
	}
	return (((unsigned char *)s1)[counter] - ((unsigned char *)s2)[counter]);
}

//ft_strlen
int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

//ft_lstsize
int	ft_lstsize(t_env *lst)
{
	size_t	count;

	count = 0;
	while (lst && ++count)
		lst = lst->next;
	return (count);
}

//ft_split
static size_t	ft_wordcount(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		while (s[i] != c && s[i])
			i++;
		count++;
		while (s[i] == c && s[i])
			i++;
	}
	return (count);
}

static char	*stringf(const char *s, char c)
{
	char	*temp;
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	temp = (char *)malloc(sizeof(char) * (i + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	**ft_split(const char *s, char c)
{
	char	**temp;
	int		wordc;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	wordc = ft_wordcount(s, c);
	temp = (char **)malloc(sizeof(char *) * (wordc + 1));
	if (!temp)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			temp[i] = stringf(s, c);
			i++;
		}
		while (*s && *s != c)
		s++;
	}
	temp[i] = NULL;
	return (temp);
}

//ft_strjoin
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		k;
	char	*temp;

	i = 0;
	k = 0;
	temp = NULL;
	if (!s1 || !s2)
		return (NULL);
	temp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + \
				ft_strlen(s2) + 1));
	if (!temp)
		return (NULL);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	while (s2[k])
	{
		temp[k + i] = s2[k];
		k++;
	}
	temp[k + i] = '\0';
	return (temp);
}

//ft_strdup
char	*ft_strdup(char *src)
{
	char	*new;
	int		i;
	int		size;

	size = 0;
	while (src[size])
		++size;
	if (!(new = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

//ft_strchr
char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

//---------------------------//

void	ft_exit(int error, char *str1, char *str2, char *str3)
{
	if (str1 == NULL)
		printf("%s", "\0");
	else
		printf(RED"%s%s%s"END, str1, str2, str3);
	if (error < 0)
		exit(0);
	/*else if (error == 0)
		printf(RED"%s: command not found\n"FINISH, str);
	else if (error == 1)
		printf(RED"%s"FINISH, str);
	else if (error == 2)
		printf(RED"cd: %s: No such file or directory\n"FINISH, str);
	else if (error == 3)
		printf(RED"export: '%s': not a valid identifier\n"FINISH, str);
	else if (error == 4)
		printf(RED"%s: Is a directory\n"FINISH, str);
	else if (error == 5)
		printf(RED"cd: %s: Not a directory\n"FINISH, str);*/
}

//girilen splitli argümanları temizliyor.
void	ft_free(char **line)
{
	int	i;

	i = -1;
	while (line[++i])
		free(line[i]);
	free(line);
}

int	ft_strcmp_edited(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp_edited(const char *s1, const char *s2, size_t n)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1 && (*s1 != '\0') && (*s1 == *s2) && n > 0)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0 && (s1[n] == ' ' || s1[n] == '\0')) // "(s1[n] == ' ' || s1[n] == '\0')" cd .. <enter> durumu, cd.. <enter> şeklinde kullanılmasını engellemek için konuldu.
		return (1);
	return (0);
}

// env yapısını listeye atamak için oluşturulmuş fonksiyon.
void	ft_env_struct(char *env_arg)
{
	t_env	*new;
	t_env	*temp;
	int		i;

	new = (t_env *)malloc(sizeof(t_env));  // yeni node alanı.
	new->data = ft_split(env_arg, '=');  //data 2 boyutlu bir array olduğunda dolayı split ile 0. indexe PWD,OLDPWD,HOME argümanlar atanır. 1.index'e uzantıları atanır.
	new->next = NULL;
	if (new->data[2] != NULL) // kendi içerisinde "=" durumları olan argümanları ekleyebilmek için özel durum oluşturdum.
	{
		i = 1;
		while (new->data[++i] != NULL)
			new->data[1] = ft_strjoin(ft_strjoin(new->data[1], "="), new->data[i]);
		new->data[2] = NULL;
	}
	if (g_main.env == NULL) // ilk durumda değer atamak için yapıyoruz.
	{
		g_main.env = new;
		g_main.env->next = NULL;
	}
	else
	{
		temp = g_main.env; //main->env listesinin sabit kalmasını istediğimizden dolayı yedek liste oluşturup eşitliyoruz.
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

//env_name PWD,HOME,OLDPWD... argümanları tutmaktadır. if koşulu ile data[0] stringi strcmp ile karşılaştırılır ve eşit ise 0 döner.
char	*ft_env_findret(char *env_name)
{
	t_env	*tmp;

	tmp = g_main.env;
	while (tmp != NULL)
	{
		if (ft_strcmp_edited(env_name, tmp->data[0]) == 0)
			return (tmp->data[1]);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_login_print(void)
{
	char	*name;

	name = ft_env_findret("NAME");
	if (name == NULL)
		name = "42kocaeli.com.tr";
	printf(GREEN"\nLOGIN INFORMATION: "RED"%s%s%s\n"END,\
		 ft_env_findret("LOGNAME"), "@" , name);
	printf("%s\n", GREEN"                _           _          "RED_BLINK
	"__  __  ______  __      __ ");
	printf("%s\n", GREEN"   ____ ___    (_) ____    (_) "BLACK"_____  "RED_BLINK
	"/ / / / / ____/ / /     / / ");
	printf("%s\n", GREEN"  / __ `__ \\  / / / __ \\  / / "BLACK"/ ___/ "RED_BLINK
	"/ /_/ / / __/   / /     / /  ");
	printf("%s\n", GREEN" / / / / / / / / / / / / / / "BLACK"(__  ) "RED_BLINK
	"/ __  / / /___  / /___  / /___");
	printf("%s\n", GREEN"/_/ /_/ /_/ /_/ /_/ /_/ /_/ "BLACK"/____/ "RED_BLINK
	"/_/ /_/ /_____/ /_____/ /_____/"END);
	printf("\n");
}

// env argümanları tek tek çağırılıp, listeye aktarılacak. getenv("PATH"); gibi çağırılacak.
void	ft_set_argument(void)
{
	int	i;

	//printf("\e[1;1H\e[2J"); // Derleme sonrasında önceki girdileri silmeye yarıyor.
	i = -1;
	g_main.env = NULL;
	while (environ[++i])
		ft_env_struct(environ[i]);
	g_main.PATH = ft_split(ft_env_findret("PATH"), ':');
	g_main.echo_val = 0;
	ft_login_print();
}

char	*ft_directory_name(char *path)
{
	char	*name;
	int		i;
	int		l;

	i = ft_strlen(path);
	l = i;
	if (i == 1)
		return ("/");
	while (path[i] != '/')
		i--;
	return (&path[++i]);
}

char	*ft_terminal_print(void)
{
	char	*name;
	char	*tmp;

	name = ft_directory_name(ft_env_findret("PWD"));
	tmp = ft_strjoin(GREEN"➟ "BLKB, name);
	name = ft_strjoin(tmp, " $ "END);
	free(tmp);
	return (name);
}

// komut satırına sadece <enter> veya "    " <enter> girdilerinin history kayıt edilmesini önlemek için.
// static olma durumu; sürekli olarak girilen(arka arkaya) komutun hafızaya alınmasına engel oluyor.
static int	ft_history_empty_check(char *str)
{
	static char	*last_entry;
	int			i;
	int			l;

	if (ft_strcmp_edited(str, last_entry) == 0) // arka arkaya girdiyi engelliyor
		return (0);
	free(last_entry); //yeni girdiyi hafıza almadan önce, 2 adım önce girilen girdinin hafızadan temizlenmesi gerekiyor.
	last_entry = ft_strdup(str);
	l = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			l++;
		i++;
	}
	//free(last_entry);
	if (i == l)
		return (0);
	return (1);
}

void	ft_detec(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_main.echo_val = 130;
	}
	else if (sig == 3)
		printf("%s", "\n");
}


int	ft_syntax_loop(int i)
{
	int first;
	int	last;
	int	lenght;
	int count;
	char token;

	token = '\0';
	first = -1;
	last = 0;
	lenght = 0;
	count = 0;
	while (g_main.input_line[i])
	{
		if (token == '\0' && g_main.input_line[i] == SHELL_QUOTE_CHARS[0] && g_main.input_line[i - 1] != SHELL_ESCAPE[0])
		{
			first = i;
			token = SHELL_QUOTE_CHARS[0];
			lenght = ++i;
			count++;
			while (g_main.input_line[lenght])
			{
				if (g_main.input_line[lenght] == SHELL_QUOTE_CHARS[0] && last == 0) //Tek tırnak içerisinde kaçış metası yok sayılıyor bu yüzden buraya eklemeye gerek yok.
				{
					last = ++lenght;
					count++;
				}
				lenght++;
			}
		}
		else if (token == '\0' && g_main.input_line[i] == SHELL_QUOTE_CHARS[1] && g_main.input_line[i - 1] != SHELL_ESCAPE[0])
		{
			first = i;
			token = SHELL_QUOTE_CHARS[1];
			lenght = ++i;
			count++;
			while (g_main.input_line[lenght])
			{
				if (g_main.input_line[lenght] == SHELL_QUOTE_CHARS[1] && last == 0 && g_main.input_line[lenght - 1] != SHELL_ESCAPE[0])
				{
					last = ++lenght;
					count++;
				}
				lenght++;
			}
		}
		i++;
	}
	if (first != -1 && last == 0)
		return (-1);
	if (count == 0)
		return (ft_strlen(g_main.input_line));
	//printf("------> last: %d\n", last);
	return (last);
}

/** 
 * input_line'da önce;
 * 		girdideki ilk operatör nedir o kontrol edilir.
 * 
 * 
 * 		girdi, tırnaklar ile başlıyor mu kontrol edilir. örn: "echo ahmet | wc -l" bu durumda girdinin tamamı komut olarak algılanır.
 * 		Çift tırnak durumu olduğu gibi tek tırnak durumuda vardır. örn: 'echo ahmet | wc -l' bu durumda da girdinin tamamı komut olarak algılanır.
 * 		Tırnak kontrolüne devam edilir ve tırnaklar çift sayıda mı kontrol edilir. Değilse terminal input durumunda olmamalıdır, hata döndürmelidir.
 * 		
 * 		
 * 
 */
int	ft_syntax(void)
{
	int	i;
	int	l;

	printf("GİRDİ: %s\n", g_main.input_line);
	i = 0;
	l = ft_strlen(g_main.input_line);
	while (i != -1)
	{
		i = ft_syntax_loop(i);
		//printf("-->%d\n", i);
		if (i == -1)
		{
			printf("Syntax Error!\n");
			return (0);
		}
		if (i == l)
			return (1);
	}
	return (1);
}

void	ft_command_run(void)
{
	printf("Çalışıyor.\n");
}

/*
> Tanım:
	> Bu proje basit bir kabuk(shell) oluşturmakla ilgilidir.
		İşlemler ve dosya tanımlayıcıları hakkındadır.
> İzin verilen fonksiyonlar:
	> readline, rl_clear_history, rl_on_new_line, rl_replace_line,
	rl_redisplay, add_history, printf, malloc, free, write, access,
	open, read, close, fork, wait, waitpid, wait3, wait4, signal,
	sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir,
	stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir,
	readdir, closedir, strerror, perror, isatty, ttyname, ttyslot,
	ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum,
	tgetstr, tgoto, tputsc

> Kabukta olması gereken özellikler:
	> Yeni bir komut beklerken bir bilgi istemi görüntüleyin. ✓
	> Girdileri hafıza tutarak history oluşturun. ✓
	> Search and launch, dosyayı arayın ve başlatın. ✓
	> Min 1 global değişken kullanılabilir. Açıklanmalıdır.
	> Kapatılmamış alıntıları veya
		özel karakterleri yorumlamayın. "\" (backslash) or ";" (semicolon)
	> Alıntılanan dizideki meta karakterlerin tek tırnak içerisinde iken engellenmesi gerekmektedir.
	> Alıntılanan dizideki $ işaretinin argüman çağırması gerektiğini tanıt.

> Uygulanması gerekenler;
	> "< should redirect input" "<" işaretnin işlevini yerine getirin.
	> "> should redirect output" ">" işaretinin işlevini yerine getirin.
	> "<< bir sınırlayıcı verilmeli"
		ardından sınırlayıcıyı içeren bir satır görülene kadar girişi okumalısınız.
		Ancak, geçmişi güncellemek zorunda değildir!
	> Boruları (| karakter) uygulayın. Boru hattındaki her komutun çıkışı,
		bir sonraki komutun girişine bir boru aracılığıyla bağlanır.
	> Değerlerine genişlemesi gereken ortam değişkenlerini ($ ardından bir karakter dizisi) kullanın.
	> $? bir önceki komut TRUE ise 0, FALSE ise 1 dönecektir. ✓
	> Bash'deki gibi davranması gereken ctrl-C, ctrl-D ve ctrl-\'yi kullanın. ✓

> Terminal ile etkileşim içinde iken:
	> ctrl-C, yeni bir satırda yeni bir bilgi istemi görüntüler. ✓
	> ctrl-D exits the shell. ✓
	> ctrl-\ does nothing. ✓

> Terminalin uygulaması gereken komutları:
	> echo with option -n ✓
	> cd with only a relative or absolute path ✓
	> pwd with no options ✓
	> export with no options ✓
	> unset with no options ✓
	> env with no options or arguments ✓
	> exit with no options ✓

> READLINE WHAT MEAN??
	> THIS MEAN IS "FUCK OFF LEAKS",
	> readline() işlevi bellek sızıntılarına neden olabilir.
	Onları düzeltmek zorunda değilsin.
	Ancak bu kendi kodunuz anlamına gelmez,
	evet yazdığınız kodda bellek sızıntısı olabilir.
*/
int main(void)
{
	ft_set_argument();
	while (1)
	{
		signal(SIGINT, ft_detec); // control-C signal, yeni bir satıra geçiş yapmalı.
		signal(SIGQUIT, ft_detec); // "control-\" , ingilizce klavyeye alıp(mac klavye) "control-," ile çalışıyor.
		g_main.terminal_name = ft_terminal_print();
		g_main.input_line = readline(g_main.terminal_name); // terminal adının silinmemesi için " " girilmesi gerekiyor, NULL durumunda siliyor. 
		if (!g_main.input_line) //control-D tuş kombinasyonu ile terminal kapatılmalı.
			ft_exit(-1, "exit\n", "\0", "\0");
		if (ft_history_empty_check(g_main.input_line)) // boş girilen satırları atlamak için. // arda arda giriş gerçekleşmiş ise yok sayılıyor.
			add_history(g_main.input_line);
		if (ft_syntax())
			ft_command_run();
		//free(g_main.input_line);
		//free(g_main.terminal_name);
		//ft_free(g_main.array_line);
		//system("leaks a.out");
	}
	return (0);
}