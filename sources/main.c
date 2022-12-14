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

/** NORMOK:
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

> Tan??m:
	> Bu proje basit bir kabuk(shell) olu??turmakla ilgilidir.
		????lemler ve dosya tan??mlay??c??lar?? hakk??ndad??r.
> ??zin verilen fonksiyonlar:
	> readline, rl_clear_history, rl_on_new_line, rl_replace_line,
	rl_redisplay, add_history, printf, malloc, free, write, access,
	open, read, close, fork, wait, waitpid, wait3, wait4, signal,
	sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir,
	stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir,
	readdir, closedir, strerror, perror, isatty, ttyname, ttyslot,
	ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum,
	tgetstr, tgoto, tputsc

> Kabukta olmas?? gereken ??zellikler:
	> Yeni bir komut beklerken bir bilgi istemi g??r??nt??leyin. ???
	> Girdileri haf??za tutarak history olu??turun. ???
	> Search and launch, dosyay?? aray??n ve ba??lat??n. ???
	> Min 1 global de??i??ken kullan??labilir. A????klanmal??d??r.
	> Kapat??lmam???? al??nt??lar?? veya
		??zel karakterleri yorumlamay??n. "\" (backslash) or ";" (semicolon)
	> Al??nt??lanan dizideki meta karakterlerin tek t??rnak i??erisinde
		iken engellenmesi gerekmektedir.
	> Al??nt??lanan dizideki $ i??aretinin arg??man ??a????rmas?? gerekti??ini tan??t.

> Uygulanmas?? gerekenler;
	> "< should redirect input" "<" i??aretnin i??levini yerine getirin.
	> "> should redirect output" ">" i??aretinin i??levini yerine getirin.
	> "<< bir s??n??rlay??c?? verilmeli"
		ard??ndan s??n??rlay??c??y?? i??eren bir sat??r g??r??lene kadar
			giri??i okumal??s??n??z.
		Ancak, ge??mi??i g??ncellemek zorunda de??ildir!
	> Borular?? (| karakter) uygulay??n. Boru hatt??ndaki her komutun ????k??????,
		bir sonraki komutun giri??ine bir boru arac??l??????yla ba??lan??r.
	> De??erlerine geni??lemesi gereken ortam de??i??kenlerini
		($ ard??ndan bir karakter dizisi) kullan??n.
	> $? bir ??nceki komut TRUE ise 0, FALSE ise 1 d??necektir. ???
	> Bash'deki gibi davranmas?? gereken ctrl-C,
		ctrl-D ve ctrl-\'yi kullan??n. ???

> Terminal ile etkile??im i??inde iken:
	> ctrl-C, yeni bir sat??rda yeni bir bilgi istemi g??r??nt??ler. ???
	> ctrl-D exits the shell. ???
	> ctrl-\ does nothing. ???

> Terminalin uygulamas?? gereken komutlar??:
	> echo with option -n ???
	> cd with only a relative or absolute path ???
	> pwd with no options ???
	> export with no options ???
	> unset with no options ???
	> env with no options or arguments ???
	> exit with no options ???

> READLINE WHAT MEAN??
	> THIS MEAN IS "FUCK OFF LEAKS",
	> readline() i??levi bellek s??z??nt??lar??na neden olabilir.
	Onlar?? d??zeltmek zorunda de??ilsin.
	Ancak bu kendi kodunuz anlam??na gelmez,
	evet yazd??????n??z kodda bellek s??z??nt??s?? olabilir.
	
> Meanings -> lexer -> parser -> expander -> executor
	LEXER: -> -Tarayici-
S??zc??k, anlams??z dizeyi "say?? de??i??mezi",
 "dize de??i??mezi", "tan??mlay??c??" veya "i??le??" gibi d??z bir
 listeye d??n????t??r??r ve ayr??lm???? tan??mlay??c??lar?? ("anahtar kelimeler")
 tan??mak ve bo??luklar?? atmak gibi ??eyler yapabilir.
Bunlara taray??c??s??z ayr????t??r??c??lar denir. Bir lexer(sozluk) ve
 bir parser(ayristirici) s??rayla ??al??????r: s??zc?? girdiyi tarar
 ve e??le??en simgeleri ??retir, ayr????t??r??c?? daha sonra simgeleri tarar ve
 ayr????t??rma sonucunu ??retir.
	PARSER: -> -Ayristirici-
Ayr????t??r??c??, ba??ka bir dile kolay ??eviri i??in verileri daha k??????k ????elere
 ay??ran bir derleyici veya yorumlay??c?? bile??enidir. Ayr????t??r??c??, bir
 dizi belirte??, etkile??imli komutlar veya program talimatlar?? bi??iminde
 girdi al??r ve bunlar?? di??er bile??enler taraf??ndan programlamada
 kullan??labilecek par??alara ay??r??r.
				DIFFERENCE - FARKLARI
	Lexer, s??zc??k analizi yapan bir yaz??l??m program??d??r.
 ... Ayr????t??r??c??, s??zc??den bir d??zey daha ileri gider ve s??zc?? taraf??ndan
 ??retilen belirte??leri al??r ve uygun t??mcelerin olu??turulup olu??turulmad??????n??
 belirlemeye ??al??????r. Ayr????t??r??c??lar dilbilgisi d??zeyinde,
 s??zl??kler s??zc??k d??zeyinde ??al??????r.
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
 *  heredoc $pwd arg??man?? ile kapat??lmas?? gerekiyor.
 * TODO: exit komutu icin command_exec()'deki return degerleri duzene cekilecek.
 * TODO: cat yazildiginda argumanlar bittikten sonra ctrl+c ile cikinca
 *  2 kere promt yazdiriyor.
 * TODO: unset PWD yapildiginda; cd - yaptigimizda
 *  "bash: cd: OLDPWD not set" yazmasi gerekiyor, bizde yazmiyor calisiyor.
 * IDK: buyuk harflerle PWD yazildiginda execve'ye gonderip calistiriyor
 *  ama pwd yazarsak kucuk harflerle bizim cmd_pwd.c calisiyor
 * 
 * TODO: unset = (env yoksa segmentation yiyior)!!!!!!!!!!! 
 * 	Bunu duzelttigimizda make test'teki segmentation'larin hepsi duzelmesi gerek.
 * TODO: signal();
 * TODO: sagdan okuma...
 * TODO: cmd_syntax....
 * TODO: heredoc onceligi var; ls > a | cat << asdf
 *  'de a dosyasi olusturulmayacak.
 * TODO: dosya yoksa hata verdirilecek.
 * 
 * TODO: . komutu error dondurmesi gerekiyor.
 * TODO: ..komutu error dondurmesi gerekiyor.
 * TODO: export asdf="/bin/echo 1"
 * 	$asdf yaptigimizda 1 yazdirmasi lazim...
 * TODO: herhangi_bir_yerde_alt_cizgi_varsa= calismiyor env'ye eklemesi lazim
 * 	ornek; export asdf_asdf=deneme
 * TODO:
 * 
OK: ls -l > 1.txt -a | cat << EOF
OK: echo "$PWD $HOME"
OK: echo "$ aaa"
OK: ls > a | cat < a
ERROR: ls > a | cat < a | cat a | pwd >> a | cat a
	Sadece en sondaki pipe ciktiyi stdout'a(1)'e verecek biz gorebilecegiz.
	2 kere calistirilinca buga giriyor.
OK: IDK: ls > a | pwd >> a | cat a
	Bash'teki cat hatali morq.
OK: ls > a | pwd >> b
OK: LOL: ls > a | pwd >> b | cat b
	Bundaki cat'te sorun yok mesela :D
OK: INTERESTING: pwd | cat << eof
	Calisiyor ama CTRL+C yaptigimizda(^C) 2 kere PROMPT yaziyor
OK: ls > a | cat << pwd
OK: echo ""echo test | ls""
OK: cd $pwd
OK: echo ""echo test | ls                                          ""
""ls | pwd""

ls | a | wc -l
unset PWD HOME OLDPWD -> cd, cd .., cd ., cd /usr/bin kontrolleri 
pwd | wc -l
echo ahmet > A ls > B
ls -l -x -a> B
ls >> A >> B << EOF
cat << EOF
A << EOF
wc -l < A
ls > A << EOF
pwd >> A << EOF
cat < A
echo A << EOF
echo > A
pwd >> A
echo ahmet >> A

ls -l >> A > B
ls > A | pwd > B | cat < A
pwd | cat
 * 
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
