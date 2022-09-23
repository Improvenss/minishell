/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:41:13 by gsever            #+#    #+#             */
/*   Updated: 2022/09/19 18:20:53 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief 
 * 	1.While döngüsünde varsa pipe operatörünün solu kontrol ediliyor,
 * 		bu aşamada space karakteri ne kadar kullanmış kontrol ediliyor,
 * 		pipe'ın bulunduğu index konumuna kadar
 * 			 space karakteri sayısı karşılaştırılıyor,
 * 		eğerki eşitlik söz konusu ise -1 döndürülüyor.
 * 		pipe kullanılmamış ise (token == '\0') kendi uzunluğu döndürülüyor.
 * 
 * 	2.While döngüsünde varsa pipe operatörünün solu kontrol ediliyor,
 * 		eğer pipe yok ise bu döngüye girmiyor.
 * 		Girdiği durumda ise pipe görene kadar veya girdi sonuna kadar
 * 			okumaya devam ediyor, bu sırada boş karakterler sayılır
 * 			ve ikinici pipe'ın bulunduğu/string sonu index'inden
 * 			birinci pipe'ın index'i çıkarılıyor ve eşitliği
 * 			pipe'ın solundaki space karaterlerine eşit ise
 * 			-1 dönüyor.
 * 		
 * @param i
 * @fn ft_strlen()
 * @return int 
 */
int	syntax_pipe(int i)
{
	int		count;
	char	token;
	int		k;
	int		l;

	count = 0;
	token = '\0';
	l = 0;
	while (g_main.input_line[i] && token == '\0')
	{
		if (token == '\0' && g_main.input_line[i] == SHELL_META_CHARS[0] && g_main.input_line[i - 1] != SHELL_ESCAPE[0])
			token = SHELL_META_CHARS[0];
		if (g_main.input_line[i] == 32)
			count++;
		i++;
	}
	k = i;
	while (g_main.input_line[k] && g_main.input_line[k] != SHELL_META_CHARS[0] && g_main.input_line[i - 1] != SHELL_ESCAPE[0])
	{
		if (g_main.input_line[k] == 32)
			l++;
		k++;
	}
	if (token == '\0')
		return (ft_strlen(g_main.input_line));
	if ((token != '\0' && count == i - 1) || k - i == l)
		return (-1);
	return (i);
}
