/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:16:13 by gsever            #+#    #+#             */
/*   Updated: 2022/10/06 13:51:41 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

// Tokenler icin numara defineleri.
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

/* ************************************************************************** */
/* STRUCT DEFINES AREA													  	  */
/* ************************************************************************** */

/**
 * @brief Tokenleri chmod'daki gibi 2^ olarak aliyor.
 * 
 * @param flags 
 * @param str* 
 */
typedef struct s_token_content
{
	int		flags;
	char	*str;
}	t_new_token;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// token.c
t_list		*token_create(char *string, int type);
char		*token_to_str(t_list *token);
bool		token_is_cmd(t_list *token);
t_new_token	*token_content(t_list *token);
void		new_token_destroy(void *new_token);

#endif