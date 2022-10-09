/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:47:58 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/09 16:28:54 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/** OK:
 * @brief Set the arg object
 * 
 * Environ'larin hepsini char **environ'dan satir satir char dizisi olacak
 *  sekilde aliyor, 
 * 
 * @param base 
 * @param environ 
 * @fn env_struct(): envp'lerin hepsini satir satir aliyor,
 *  ='in sol tarafini data[0],
 *  ='in sag tarafini data[1] olarak ayirip(splitleyip) t_env structuna
 *  linked list olacak sekilde atiyor.
 * @fn env_findret(): env_struct()'ta ayrilan base->env'e yazilan
 *  environmentlerimizin icinden "PATH"i ariyor ve env'nin data[1]'ini donuyor.
 * @fn ft_split(): PATH= environmen'ini alip ':' ile biten kismi ayiriyor,
 *  bunlari konum calistirirken kullanacagiz.
 * ETC:	PATH=
 * 			 /opt/homebrew/bin: -> base->PATH[0] 
 * 			/opt/homebrew/sbin: -> base->PATH[1]
 * 				/usr/local/bin: -> base->PATH[2]
 * 					  /usr/bin: -> base->PATH[3]
 * 						  /bin: -> base->PATH[4]... diye yaziyor.
 * @fn strerror(): INT seklinde girilen error'un stringini donduruyor.
 * @fn print_error(): Bash'teki gibi error ciktisi verebilmek icin.
 * @return int ERROR: err_code. OK: 0.
 */
int	set_arg(t_base *base, char **environ)
{
	int	i;

	base->env = NULL;
	i = -1;
	while (environ[++i])
		env_struct(base, environ[i]);
	base->PATH = ft_split(env_findret(base, "PATH"), ':');
	if (base->PATH == NULL)
		return (print_error(T_NAME, NULL, NULL, strerror(ENOMEM)));
	return (0);
}

/** OK:
 * @brief Main.
 * 
 * brew install comands in /goinfre/$USER
 * 
1. STEP: git clone --depth=1 https://github.com/Homebrew/brew \
/goinfre/$USER/brew \
&& echo 'export PATH=/goinfre/$USER/brew/bin:$PATH' >> $HOME/.zshrc

2. STEP: brew install readline
3. STEP: brew link --force readline
4. STEP: echo 'export C_INCLUDE_PATH="/goinfre/$USER/brew/\
include:$C_INCLUDE_PATH"' >> ~/.zshrc
5. STEP: echo 'export LIBRARY_PATH="/goinfre/$USER/brew/\
lib:$LIBRARY_PATH"' >> ~/.zshrc

 * 
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
	> Alıntılanan dizideki meta karakterlerin tek tırnak içerisinde
		iken engellenmesi gerekmektedir.
	> Alıntılanan dizideki $ işaretinin argüman çağırması gerektiğini tanıt.

> Uygulanması gerekenler;
	> "< should redirect input" "<" işaretnin işlevini yerine getirin.
	> "> should redirect output" ">" işaretinin işlevini yerine getirin.
	> "<< bir sınırlayıcı verilmeli"
		ardından sınırlayıcıyı içeren bir satır görülene kadar
			girişi okumalısınız.
		Ancak, geçmişi güncellemek zorunda değildir!
	> Boruları (| karakter) uygulayın. Boru hattındaki her komutun çıkışı,
		bir sonraki komutun girişine bir boru aracılığıyla bağlanır.
	> Değerlerine genişlemesi gereken ortam değişkenlerini
		($ ardından bir karakter dizisi) kullanın.
	> $? bir önceki komut TRUE ise 0, FALSE ise 1 dönecektir. ✓
	> Bash'deki gibi davranması gereken ctrl-C,
		ctrl-D ve ctrl-\'yi kullanın. ✓

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

int	main(int argc, char *argv[], char *envp[])
NOT: char *envp[] -> environment pointer.

http://unixwiz.net/techtips/gnu-c-attributes.html

int	main(int argc __attribute((unused))
	, char **argv __attribute((unused))
	, char **envp)

int	main(int argc __unused, char **argv __unused, char **environ)

> Meanings -> lexer -> parser -> expander -> executor
	LEXER: -> -Tarayici-
Sözcük, anlamsız dizeyi "sayı değişmezi",
 "dize değişmezi", "tanımlayıcı" veya "işleç" gibi düz bir
 listeye dönüştürür ve ayrılmış tanımlayıcıları ("anahtar kelimeler")
 tanımak ve boşlukları atmak gibi şeyler yapabilir.
Bunlara tarayıcısız ayrıştırıcılar denir. Bir lexer(sozluk) ve
 bir parser(ayristirici) sırayla çalışır: sözcü girdiyi tarar
 ve eşleşen simgeleri üretir, ayrıştırıcı daha sonra simgeleri tarar ve
 ayrıştırma sonucunu üretir.
	PARSER: -> -Ayristirici-
Ayrıştırıcı, başka bir dile kolay çeviri için verileri daha küçük öğelere
 ayıran bir derleyici veya yorumlayıcı bileşenidir. Ayrıştırıcı, bir
 dizi belirteç, etkileşimli komutlar veya program talimatları biçiminde
 girdi alır ve bunları diğer bileşenler tarafından programlamada
 kullanılabilecek parçalara ayırır.
				DIFFERENCE - FARKLARI
	Lexer, sözcük analizi yapan bir yazılım programıdır.
 ... Ayrıştırıcı, sözcüden bir düzey daha ileri gider ve sözcü tarafından
 üretilen belirteçleri alır ve uygun tümcelerin oluşturulup oluşturulmadığını
 belirlemeye çalışır. Ayrıştırıcılar dilbilgisi düzeyinde,
 sözlükler sözcük düzeyinde çalışır.
	EXPANDER: -> -Birlestirici-
	EXECUTOR: -> -Calistirici(Yurutucu)-
 
 * @param argc __attribute: Kullanmadigimiz durumda error gostermiyor.
 * @param argv*[] __attribute: Kullanmadigimiz durumda error gostermiyor.
 * @param envp*[]: environments
 * 
 * @fn env_init(): Program baslatma konumlarini falan hafizasinda tutan
 *  degiskenler.
 * @fn get_input(): readline() ile terminale yazilan girdiyi
 *  string tipinde aldigimiz func().
 * @fn isatty(): Terminal(tty) var mi yok mu onu kontrol ediyor.
 * @fn ft_putendl_fd(): libft-> file descriptor'a istedigimiz str'yi yazar.
 * @fn process_input(): get_input()'tan aldigimiz girdiyi calistiriyoruz.
 * @fn ft_free_split(): Ozel olarak yazilmis split icin teker teker
 *  free'leme islemi yapiyor.
 * @fn exec_exit_status_get(): return/error degerimiz icin kullaniyoruz,
 *  boylelikle girdi hangi err kodunu donduruyor onu anlayabiliyoruz.
 * 
 * @return int 
 */
int	main(int argc __attribute((unused))
	, char **argv __attribute((unused))
	, char **envp)
{
	t_base	base;

	if (set_arg(&base, envp) == ERROR)
		exit(EXIT_FAILURE);
	cmd_init(&base);
	minishell(&base);
	return (0);
}
