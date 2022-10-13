/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:39:15 by gsever            #+#    #+#             */
/*   Updated: 2022/10/06 13:41:54 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "minishell.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

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

typedef struct s_redir_undo_content
{
	int		fd_repl;
	int		fd_repl_dup;
}	t_c_redir_undo;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// redir.c
int	redir_type(char *redir);

#endif