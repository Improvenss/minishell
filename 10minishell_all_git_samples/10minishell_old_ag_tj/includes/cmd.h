/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:19:19 by gsever            #+#    #+#             */
/*   Updated: 2022/10/06 13:25:21 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "minishell.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define CMD_SCMD		1

# define CMD_AND		2
# define CMD_OR			4
# define CMD_PIPE		8

# define CMD_O_BRACKET	16
# define CMD_C_BRACKET	32

# define CMD_PIPELINE	64
# define CMD_GROUP		128

# define CMD_L_SCMD		256
# define CMD_L_CMD		512

/* ************************************************************************** */
/* STRUCT DEFINES AREA													  	  */
/* ************************************************************************** */

typedef struct s_scmd_content
{
	int		type;
	t_list	*l_argv;
	t_list	*l_redir;
}	t_c_scmd;

typedef struct s_cmd_content
{
	int		type;
	t_list	*l_element;
}	t_c_cmd;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// cmd.c
t_list		*cmd_create(int type);
int			cmd_type_from_token(t_list *token);
int			cmd_type(t_list *cmd);
t_c_cmd		*cmd_content(t_list *cmd);
void		c_cmd_destroy(void *c_cmd);

// parser_scmd.c
void		c_scmd_destroy(void *c_scmd);

// scmd.c
t_list		*scmd_create(int type);
t_c_scmd	*scmd_content(t_list *scmd);
void		c_scmd_destroy(void *c_scmd);

#endif
