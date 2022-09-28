/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:37:09 by akaraca           #+#    #+#             */
/*   Updated: 2022/09/28 12:24:50 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Pipe(|)'a göre string kaç ayrı parçaya bölündüğü hesaplanır.
 * 	Count = 1;'dir, sebebi, pipe olmadığı sürece en az 1 string vardır.
 * 
 * @param s 
 * @return size_t 
 */
size_t	word_count(char *s)
{
	size_t	count;
	size_t	i;

	count = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == '|' && s[i + 1] != '|' && s[i - 1] != '|')
			count++;
		i++;
	}
	return (count);
}

/**
 * @brief Pipe(|)'dan sonraki gönderilen string yapısı,
 * 		pipe(|) görene kadar char *new; üzerine değerleri
 * 		eşitler.
 * 
 * 	Fonksiyon içeriği;
 * 	->Birinci While();
 * 		String '\0' olmadığı sürece ve index pipe(|) olmadığı veya
 * 			pipe olup, sağında veya solunda pipe olduğu sürece i'yi arttır.
 * 		Bu döngü ile pipe'lar arasındaki string uzunluğu bulunuyor.
 * 
 * 	->İkinci While();
 * 		String '\0' olmadığı sürece ve index pipe(|) olmadığı veya
 * 			pipe olup, sağında veya solunda pipe olduğu sürece index
 * 			eşitlmesi yap.
 * 
 * @param s 
 * @return char* Pipe(|)'dan bağımsız stringler döndürülür.
 */
char	*alloc(char *s)
{
	char	*new;
	int		i;

	i = 0;
	while (s[i] && (s[i] != '|' \
	|| (s[i] == '|' && (s[i - 1] == '|' || s[i + 1] == '|'))))
		i++;
	new = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] && (s[i] != '|' \
	|| (s[i] == '|' && (s[i - 1] == '|' || s[i + 1] == '|'))))
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

/**
 * @brief base->input_line yapısını 
 * 	2 boyutlu array'a dönüştürürken pipe'a göre böldük,
 * 	lakin pipe(|) ile or(||) aynı simgeye sahip olduklarından dolayı 
 * 	hatalı bölme işlemi gerçekleştiriyordu,
 * 	bu yüzden bu duruma özel olarak split funk. yazıldı.
 * 
 * 	Fonksiyon içeriği:
 * 	->int l;
 * 		char *s; üzerinde ilerlemeyi sağlayan valuedir.
 * 
 * 	->int i;
 * 		new[i]; 2 boyutlu array'in yapısını belirtir.
 * 
 * 	->İkinci while();
 * 		İlk durum için bir işlevi yoktur 
 * 			lakin string ilerledikçe işleme girecektir.
 * 		String '\0' olmadığı sürece ve bulunduğu index tek pipe
 * 		yapısına sahip olduğu sürece l'yi arttır.
 * 
 * 	->if ();
 * 		Tek pipe yapısını atladıktan sonra 2 boyutlu dizenin
 * 			içeriklerinin oluşturulması için kullanılan yapıdır.
 * 		(&s[l]) şeklinde gönderilmesinin sebebi, l'nin bulunduğu
 * 			index konumunda sonra yer alan string işleme gönderilecektir.
 * 
 * 	->Üçüncü while();
 * 		String '\0' olmadığı sürece ve bulunduğu index pipe olmadığı veya
 * 			pipe olup, sağında veya solunda pipe olduğu sürece l'yi arttır.
 * 		Burada | simgesinde ilerleme olmadığı, || simgesinde ilerme
 * 			olduğu anlamına gelmektedir.
 * 
 * 	->new[i] = NULL;
 * 		2 boyutlu string array'inde string yapısında olduğu gibi NULL
 * 			durumu belirtilmelidir.
 * 
 * @param s base->input_line değeri gelmektedir.
 * @fn word_count(); Stringin pipe'a bölümü durumda 
 * 	kaç parçaya ayrılacağını değeri bulunmaktadır.
 * @fn alloc(); Oluşturulan 2 boyutlu array'in içeriğini oluşturmak için 
 * 	yönlendirilen fonk.'dur.
 * @return char** base->input_line ---> base->array_line
 */
char	**pipe_split(char *s)
{
	char	**new;
	int		wordc;
	int		l;
	int		i;

	wordc = word_count(s);
	new = (char **)malloc(sizeof(char *) * (wordc + 1));
	l = 0;
	i = 0;
	while (s[l])
	{
		while (s[l] && (s[l] == '|' && (s[l - 1] != '|' || s[l + 1] != '|')))
			l++;
		if (s[l])
		{
			new[i] = alloc(&s[l]);
			i++;
		}
		while (s[l] && (s[l] != '|' || (s[l] == '|' \
		&& (s[l - 1] == '|' || s[l + 1] == '|'))))
			l++;
	}
	new[i] = NULL;
	return (new);
}
