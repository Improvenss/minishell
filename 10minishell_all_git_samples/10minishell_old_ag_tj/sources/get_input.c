/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:44:19 by gsever            #+#    #+#             */
/*   Updated: 2022/10/06 17:20:19 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Terminal'e yazilan girdiyi aliyor.
 * 
 * input'taki stringi;
 * 	LEXER: tokenlerini aliyor.
 * 	PARSER: Tokenleri parcalayip cmd(command)'ye donusturuyor.
 * 	EXPANDER: cmd'leri birlestirip.
 * 	EXECUTOR: Yurutuyorsun.
 * 
 * @param input 
 * @fn signal()
 * @fn lexer() Alinan girdi icin ilk kontrol kismi.
 *  Syntaxlarina burada bakiyor.
 * @fn free()
 * 
 */
void	process_input(char *input)
{
	t_list	*l_token;
	t_list	*l_parser;

	signal(SIGINT, SIG_IGN);
	errno = 0;
	l_token = NULL;
	l_parser = NULL;
	l_token = lexer(input);
	free(input);
	if (l_token != NULL)
		l_parser = parser(l_token);
}

/**
 * @brief Readline ile terminal girdisi okunup return ediliyor.
 * 
 * [ input ]&& input[0]
 * sondaki str'nin NULL durumunu kontrol ediyor.
 * input && [ input[0] ]
 * str'nin ilk argumani NULL durumunu kontrol ediyor.
 * 
 * @param input 
 * @return char* -> input
 */
char	*get_input(char *input)
{
	if (isatty(STDIN_FILENO))
		input = readline(PROMPT);
	if (input == NULL)
		return (NULL);
	else if (isatty(STDIN_FILENO) && input && input[0])
		add_history(input);
	return (input);
}
