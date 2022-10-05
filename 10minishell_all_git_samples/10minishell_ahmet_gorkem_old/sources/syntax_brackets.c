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

int	syntax_brackets_near_reverse(t_base *base)
{
	int	i;
	int	first;
	int	last;
	int	count;

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

int	syntax_brackets_near(t_base *base)
{
	int	i;
	int	first;
	int	last;
	int	count;

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

/**
 * @brief 
 * 
 * @param base 
 * @param i 
 * @return int 
 */
int	syntax_brackets(t_base *base, int i)
{
	init_syntax_brackets(base);
	if (syntax_brackets_near(base) || syntax_brackets_near_reverse(base))
		return (-1);
	while (base->input_line[i])
	{
		if (base->input_line[i] == '"' || base->input_line[i] == '\'') //(("()")) en içteki parantezler arası boş ve tırnak ile string yapıyoruz bu sayede hata vermiyor.
		{
			base->sb.token = base->input_line[i];
			i++;
			while (base->input_line[i] != base->sb.token)
				i++;
			base->sb.token = '\0';
		}
		if (base->input_line[i] == '(') // sol taraftakiler sayılır.
			base->sb.left++;
		if (base->input_line[i] == ')') //sağ taraftakiler sayılır.
			base->sb.right++;
		if (base->sb.right == 0 && base->input_line[i] == '(') //son '(' işaretinin konumunu tutuyor bu sayede bir sonraki ')' ile durumu kontrol edilebiliniyor.
			base->sb.last = i;
		if (base->sb.right == base->sb.left && base->input_line[i] == ')') //parantezi kapatacak olan ) olduğundan dolayı ')'.
		{
			if ((base->input_line[base->sb.last + 1] == 32 && base->input_line[base->sb.last + 2] == ')') || base->input_line[base->sb.last + 1] == ')') // () (	 ) durumu önlemek için.
				return (-1);
			return (i + 1);
		}
		i++;
	}
	if (base->sb.right != 0 || base->sb.left != 0) //döngü çıkışında iki durumdan biri 0 değilse hatalıdır. Hatasız bir syntax ise while içerisindeki if'den çıkış gerçekleşir.
		return (-1);
	return (ft_strlen(base->input_line));
}

int	brackets(t_base *base)
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
