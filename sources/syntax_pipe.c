/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 10:34:10 by akaraca           #+#    #+#             */
/*   Updated: 2022/09/24 10:34:10 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int syntax_pipe(t_base *base, int i)
{
    while (base->input_line[i])
    {
        if (base->input_line[i] == '|' && base->input_line[i + 1] == '|' && look_the_quote(base->input_line, i)) // '||'
        {
            if (base->input_line[i + 2] == '|' || (base->input_line[i + 3] == '|' && base->input_line[i + 2] == 32 && look_the_quote(base->input_line, i))) // '|||' veya '|| |'
                return (0);
        }
        if (base->input_line[i] == '|' && base->input_line[i + 1] == 32 && base->input_line[i + 2] == '|' && look_the_quote(base->input_line, i)) // '| |' 
            return (0);
        if (base->input_line[i] == '|' && (base->input_line[i + 1] == ')' || (base->input_line[i + 1] == 32 && base->input_line[i + 2] == ')')) && look_the_quote(base->input_line, i)) // '|)' veya '| )' hatalı bir kullanımdır.
            return (0);
        if (base->input_line[i] == '|' && (base->input_line[i - 1] == '(' || (base->input_line[i - 1] == 32 && base->input_line[i - 2] == '(')) && look_the_quote(base->input_line, i)) // '(|' veya '( |' hatalı bir kullanımdır.
            return (0);
        i++;
    }
    return (1);
}

int the_pipe(t_base *base)
{
    if (base->input_line[0] == '|' || base->input_line[ft_strlen(base->input_line) - 1] == '|'
        || !syntax_pipe(base, 0))
        printf("pipe: Syntax Error!\n");
    else
        return (1);
    return (0);
}
