/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:21:42 by akaraca           #+#    #+#             */
/*   Updated: 2022/09/24 11:21:42 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int syntax_brackets_near_reverse(t_base *base)
{
    int i;
    int first;
    int last;
    int count;

    i = ft_strlen(base->input_line) - 1;
    while (i >= 0)
    {
        count = 0;
        first = -1;
        last = -1;
        while (i >= 0) // birinci ve ikinci ')' bulmak için.
        {
            if (base->input_line[i] == ')' && first == -1
                && look_the_quote(base->input_line, i))
                first = i;
            i--;
            if (base->input_line[i] == ')' && last == -1 && look_the_quote(base->input_line, i))
            {
                last = i;
                break;
            }
        }
        while (first != -1 && last != -1 && --first > last && base->input_line[first] != '|' && base->input_line[first] != '&' && base->input_line[first] != ')')
        {
            if (base->input_line[first] != 32) //boşluk, |, ||, && harici karakterleri saydırmak için.
                count++;
        }
        if (first == last && count > 0 && base->input_line[first] == ')')
            return (1);// eğerki iki aynı parantez içerisinde sadece string var ise |,|| veya && yok ise hata dönmelidir.
    }
    return (0);
}

int syntax_brackets_near(t_base *base)
{
    int i;
    int first;
    int last;
    int count;

    i = 0;
    while (base->input_line[i])
    {
        count = 0;
        first = -1;
        last = -1;
        while (base->input_line[i]) // birinci ve ikinci '(' bulmak için.
        {
            if (base->input_line[i] == '(' && first == -1 && look_the_quote(base->input_line, i))
                first = i;
            i++;
            if (base->input_line[i] == '(' && last == -1 && look_the_quote(base->input_line, i))
            {
                last = i;
                break;
            }
        }
        while (first != -1 && last != -1 && ++first < last && base->input_line[first] != '|' && base->input_line[first] != '&' && base->input_line[first] != '(')
        {
            if (base->input_line[first] != 32) //boşluk, |, ||, && harici karakterleri saydırmak için.
                count++;
        }
        if (first == last && count > 0 && base->input_line[first] == '(')
            return (1);// eğerki iki aynı parantez içerisinde sadece string var ise |,|| veya && yok ise hata dönmelidir.
    }
    return (0);
}

int syntax_brackets(t_base *base, int i)
{
    int last;
    int right;
    int left;

    right = 0;
    left = 0;
    last = 0;
    int token = '\0';
    if (syntax_brackets_near(base) || syntax_brackets_near_reverse(base))
        return (-1);
    while (base->input_line[i])
    {
        if (base->input_line[i] == '"' || base->input_line[i] == '\'') //(("()")) en içteki parantezler arası boş ve tırnak ile string yapıyoruz bu sayede hata vermiyor.
        {
            token = base->input_line[i];
            i++;
            while (base->input_line[i] != token)
                i++;
            token = '\0';
        }
        if (base->input_line[i] == '(') // sol taraftakiler sayılır.
            left++;
        if (base->input_line[i] == ')') //sağ taraftakiler sayılır.
            right++;
        if (right == 0 && base->input_line[i] == '(') //son '(' işaretinin konumunu tutuyor bu sayede bir sonraki ')' ile durumu kontrol edilebiliniyor.
            last = i;
        if (right == left && base->input_line[i] == ')') //parantezi kapatacak olan ) olduğundan dolayı ')'.
        {
            if ((base->input_line[last + 1] == 32 && base->input_line[last + 2] == ')') || base->input_line[last + 1] == ')') // () (     ) durumu önlemek için.
                return (-1);
            return (i + 1);
        }
        i++;
    }
    if (right != 0 || left != 0) //döngü çıkışında iki durumdan biri 0 değilse hatalıdır. Hatasız bir syntax ise while içerisindeki if'den çıkış gerçekleşir.
        return (-1);
    return (ft_strlen(base->input_line));
}

int		brackets(t_base *base)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(base->input_line);
	while (i != -1)
	{
		i = syntax_brackets(base, i);
		if (i == -1)
		{
			printf("brackets: Syntax Error!\n");
			return (0);
		}
		if (i == l)
			return (1);
	}
    return (0);
}
