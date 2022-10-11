/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:27:26 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/10 12:41:39 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free(t_lexer **lexer)
{
	t_lexer *tmp;

	while (*lexer != NULL)
	{
		tmp = (*lexer)->next;
		free((*lexer)->str);
		free(*lexer);
		(*lexer) = tmp;
	}
	*lexer = NULL;
}

/**
 * @brief 
 * 
 * @param base 
 * @fn lexer_list(): Lexer isleminde; operatorleri, yazim hatalarini falan
 *  kontrol edip tokenlerine ayiriyor.
 * @fn lexer_syntax(): Lexerleme isleminden sonra syntax(yazim hatasi)
 *  var mi onlari kontrol ediyor.
 * @fn redir_mark_files(): '<' '>' gibi redir operatorleri var mi onlari
 *  kontrol ediyor.
 * @fn parser(): Lexer'lenen input'u parcaliyor(parser).
 */
void	processes(t_base *base)
{
	base->lexer = NULL;
	base->parser = NULL;
	base->exit_status = 0;
	lexer(base, base->input_line);
	if (lexer_syntax(base->lexer) == ERROR
	|| redir_mark_files(base->lexer) == ERROR)
		base->exit_status = ERR_SYNTAX_EXIT;
	if (base->lexer != NULL && base->exit_status != ERR_SYNTAX_EXIT)
		parser(base);
	// if (base->lexer != NULL && base->parser != NULL)
	// 	exec_recursive(base);
}

/** OK:
 * @brief Minishell starting here.
 * 
 * @param base: Main structure.
 * @fn signal(SIGQUIT, SIG_IGN): Klayeden girilen CTRL+C,D,\ sinyallerini
 *  kontrol ediyor. SIGQUIT: CTRL+\ signalini, (SIG_IGN) ignorluyor.
 * @fn action(): CTRL+*'dan gelen sinyal sonucunda hangi func()
 *  calismasini istedigimiz func().
 * @fn readline(): T_NAME'yi terminale yazip, input'umuzu girmemizi bekliyor.
 *  Input'umuzu girdikten sonra bunu base->input_line'ye yaziyor.
 * @fn ft_putendl_fd(): input_line'miz bossa file descriptor(fd)'a error yazar.
 * @fn rl_clear_history(): readline kutuphanesi icin gecmisi temizliyor.
 * @fn exit(): Exit BRUH.
 * @fn history_empty_check(): Terminal gecmisini kontrol ediyor,
 *  static char *last_entry'de tutuyor onceki girdiyi.
 *  If tekrardan ayni girdi girildiyse return 0.
 * @fn add_history(): readline'nin kendi func(), kendisi hafizasinda tutuyor.
 * @fn processes(): base->input_line'yi alip calistiriyor,
 *  lexer -> parser -> expander -> executor islemlerini uyguluyor.
 */
void	minishell(t_base *base)
{
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, action);
		base->input_line = readline(T_NAME);
		if (!base->input_line)
		{
			ft_putendl_fd(RED"exit"END, STDERR_FILENO);
			rl_clear_history();
			exit(0);
		}
		if (history_empty_check(base->input_line))
			add_history(base->input_line);
		processes(base);
		ft_free(&base->lexer);
		free(base->input_line);
		// system("leaks minishell");
	}
	rl_clear_history();
	//ft_free(base);
	//exit(base->exit_status);
}
