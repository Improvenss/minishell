/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:44:43 by gsever            #+#    #+#             */
/*   Updated: 2022/09/23 15:36:23 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @author Gorkem SEVER (gsever)
 * @author Ahmet KARACA (akaraca)
 * @brief 
 * @version 0.1
 * @date 2022-09-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../includes/minishell.h"

extern char	**g_env;

/**
 * @brief 
 * 
 * brew install comands in /goinfre/$USER
 * 
step 1 git clone --depth=1 https://github.com/Homebrew/brew
/goinfre/$USER/brew
&& echo 'export PATH=/goinfre/$USER/brew/bin:$PATH' >> $HOME/.zshrc

step 2 brew install readline
step 3 brew link --force readline
step 4 echo 'export C_INCLUDE_PATH="/goinfre/$USER/brew/
include:$C_INCLUDE_PATH"'
>> ~/.zshrc
step 5 echo 'export LIBRARY_PATH="/goinfre/$USER/brew/
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
 * 
 * @return int 
 */
int	main(void)
{
	minishell();
	return (0);
}
