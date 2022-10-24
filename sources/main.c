/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:42:56 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/13 08:42:56 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @author Ahmet KARACA (akaraca)
 * @author Gorkem SEVER (gsever)
 * @brief 
 * @version 0.1
 * @date 2022-08-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../includes/minishell.h"

/**
 * @brief Set the arg object from main's 3. arguman.
 * 
 * base->cmd, env, lexer init'lerini yapiyor.
 * 
 * @param base For base->env_path.
 * @param environ envp from main func.
 * @fn env_struct()
 * @fn env_free()
 * @fn exit_status()
 * @fn print_error()
 * @fn strerror()
 * @fn ft_split()
 * @fn env_findret()
 * @return int OK: 0, NOK: ERROR(-1)
 */
int	set_arg(t_base *base, char **environ)
{
	int	i;

	base->env_chr = NULL;
	base->cmd = NULL;
	base->env = NULL;
	base->lexer = NULL;
	i = -1;
	while (environ[++i])
	{
		if (env_struct(base, environ[i]) == ERROR)
		{
			exit_status(ENOMEM, 0);
			return (print_error(SHELLNAME, "env", NULL, strerror(ENOMEM)));
		}
	}
	base->mem_1 = env_findret(base, "PATH");
	base->env_path = ft_split(base->mem_1, ':');
	if (base->env_path == NULL)
	{
		exit_status(ENOMEM, 0);
		return (print_error(T_NAME, "env_path", NULL, strerror(ENOMEM)));
	}
	free(base->mem_1);
	return (0);
}

/**
 * @brief Main.
 * 
 * brew install comands in /goinfre/$USER
 * 
* ************************************************************************** *

				You can use this area in makefile.
						make brew_readline

1. STEP: git clone --depth=1 https://github.com/Homebrew/brew \
/goinfre/$USER/brew \
&& echo 'export PATH=/goinfre/$USER/brew/bin:$PATH' >> $HOME/.zshrc

2. STEP: brew install readline
3. STEP: brew link --force readline
4. STEP: echo 'export C_INCLUDE_PATH="/goinfre/$USER/brew/\
include:$C_INCLUDE_PATH"' >> ~/.zshrc
5. STEP: echo 'export LIBRARY_PATH="/goinfre/$USER/brew/\
lib:$LIBRARY_PATH"' >> ~/.zshrc

* ************************************************************************** *

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
	EXECUTOR: -> -Calistirici-
 * 
 * @fn set_arg(): envp'le aldigimiz environmen'lerimizi base->env
 *  structuna atiyoruz(set ediyoruz).
 * @fn minishell(): Buradan itibaren basliyor bash shell'imiz.
 * @fn exit_status(): bash'tan cikildiktan sonra 0'la return ediyoruz.
 * 
 * NOTE: malloc() durumlari kontrol edilecek
 * TODO: malloc()
 * 	if (malloc == NULL),
 * TODO: cd'nin leaks'leri giderilecek,
 * TODO: < operatoru olusturulmayan dosya gordugunde hata
 * 	dondurmeli -> islemi durdurmali,
 * TODO: norminette icin ayirma islemi yapilacak,
 * TODO: unset icin leaks var; exportlama islemi yapildiktan sonra
 *  tekrar unset yapilirsa malloc_error_break hatasi.
 * TODO: cat << $pwd -> $pwd'nin expand edilmemesi gerekiyor,
 *  heredoc $pwd argümanı ile kapatılması gerekiyor.
 * TODO: exit komutu icin command_exec()'deki return degerleri duzene cekilecek.
 * TODO: cat yazildiginda argumanlar bittikten sonra ctrl+c ile cikinca
 *  2 kere promt yazdiriyor.
 * TODO: unset PWD yapildiginda; cd - yaptigimizda
 *  "bash: cd: OLDPWD not set" yazmasi gerekiyor, bizde yazmiyor calisiyor.
 * IDK: buyuk harflerle PWD yazildiginda execve'ye gonderip calistiriyor
 *  ama pwd yazarsak kucuk harflerle bizim cmd_pwd.c calisiyor
 * @return int 
 */
int	main(int argc __attribute((unused))
	, char **argv __attribute((unused))
	, char **envp)
{
	t_base	base;

	if (set_arg(&base, envp) != ERROR)
		minishell(&base);
	return (exit_status(0, 1));
}
