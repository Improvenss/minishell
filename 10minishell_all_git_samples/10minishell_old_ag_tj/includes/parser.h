/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:47:22 by gsever            #+#    #+#             */
/*   Updated: 2022/10/06 12:49:44 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */



/* ************************************************************************** */
/* STRUCT DEFINES AREA													  	  */
/* ************************************************************************** */



/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// parser_init.c
t_list	*parser_scmd_tokens(t_list *l_token);
t_list	*parser(t_list *l_token);

#endif