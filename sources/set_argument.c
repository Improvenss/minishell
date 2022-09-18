/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_argument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 02:48:55 by gsever            #+#    #+#             */
/*   Updated: 2022/09/18 03:15:59 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * env_name PWD,HOME,OLDPWD... argümanları tutmaktadır. If koşulu ile
 * 	data[0] stringi strcmp ile karşılaştırılır ve eşit ise 0 döner.
 * 
 * @param env_name 
 * @fn ft_strcmp_edited()
 * @return char* 
 */
char	*ft_env_findret(char *env_name)
{
	t_env	*tmp;

	tmp = g_main.env;
	while (tmp != NULL)
	{
		if (ft_strcmp_edited(env_name, tmp->data[0]) == 0)
			return (tmp->data[1]);
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * @brief 
 * 
 * @param env_arg 
 * @fn malloc()		Yeni node alani.
 * @fn ft_split()	Data 2 boyutlu bir array olduğundan dolayı split ile
 * 	0. indexe PWD,OLDPWD,HOME argümanlar atanır. 1.index'e uzantıları atanır.
 * @fn ft_strjoin()
 */
void	ft_env_struct(char *env_arg)
{
	t_env	*new;
	t_env	*temp;
	int		i;

	new = (t_env *)malloc(sizeof(t_env));
	new->data = ft_split(env_arg, '=');
	new->next = NULL;
	if (new->data[2] != NULL) // kendi içerisinde "=" durumları olan argümanları ekleyebilmek için özel durum oluşturdum.
	{
		i = 1;
		while (new->data[++i] != NULL)
			new->data[1] = ft_strjoin(ft_strjoin(new->data[1], "="), new->data[i]);
		new->data[2] = NULL;
	}
	if (g_main.env == NULL) // ilk durumda değer atamak için yapıyoruz.
	{
		g_main.env = new;
		g_main.env->next = NULL;
	}
	else
	{
		temp = g_main.env; //main->env listesinin sabit kalmasını istediğimizden dolayı yedek liste oluşturup eşitliyoruz.
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

/**
 * @brief env argümanları tek tek çağırılıp, listeye aktarılacak.
 * getenv("PATH"); gibi çağırılacak.
 * 
 * @fn ft_env_struct()
 * @fn ft_split()
 * @fn ft_env_findret()
 * @fn ft_login_print()
 */
void	ft_set_argument(void)
{
	extern char	**environ;
	int			i;

	g_main.environ = environ;
	g_main.env = NULL;  // Listeyi yeni oluşturduğumuzdan dolayı NULL'a eşitlemeliyiz.
	i = -1;
	while (g_main.environ[++i])
		ft_env_struct(g_main.environ[i]);
	g_main.PATH = ft_split(ft_env_findret("PATH"), ':'); //env içerisinde bulunan PATH'i ':' işareti ile böldük.
	g_main.echo_val = 0; //Progamı başarılı bir şekilde başlattığını varsayarak değeri 0 olmalıdır :)
	ft_login_print();
}
