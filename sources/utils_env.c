/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:19:35 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/08 23:01:25 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_env(t_base *base, char *env_name, char *new_str)
{
	t_env	*tmp;
	int		exit;

	exit = 0;
	tmp = base->env;
	while (tmp != NULL && exit == 0)
	{
		if (ft_strcmp_edited(env_name, tmp->data[0]) == 0)
		{
			tmp->data[1] = new_str;
			exit = 1;
		}
		tmp = tmp->next;
	}
}

/** OK: base->env->data[1]\
 * @brief base->env stuctunda env_name'yi ariyor,
 *  bulunca data[1]'ini donduruyor.
 * 
 * @param base base->env'ye ulasabilmemiz icin.
 * @param env_name base->env'nin icinde aramak istedigimiz env_name.
 * @fn ft_strcmp_edited(): Stringi buldugunda 0 donduruyor,
 *  bulamadiginda farkini donduruyor. Boylelikle if'e girmiyor.
 * @return char* OK: base->env->data[1] NOK: NULL
 */
char	*env_findret(t_base *base, char *env_name)
{
	t_env	*tmp;

	tmp = base->env;
	while (tmp != NULL)
	{
		if (ft_strcmp_edited(env_name, tmp->data[0]) == 0)
			return (tmp->data[1]);
		tmp = tmp->next;
	}
	return (NULL);
}

/** OK: data[0] & data[1]\
 * @brief SHELL -> data[0] = /bin/zsh -> data[1] olacak sekilde ayiriyor.
 * 
 * env yazdigimizda '='in sol tarafindaki buyuk harflerle yazilan
 *  'tanimlama ismi'ni t_env->data'sina ayirarak yazar. Ornek;
 *  SHELL=/bin/zsh
 * t_env->**data -> *data[0] = "SHELL";
 * t_env->**data -> *data[1] = "/bin/zsh"; diye ayiriyor.
 * NOT: Sadece 1 satir geliyor. Satirda'da 1 tane '=' var.
 * 
 * @param base base->env icin.
 * @param new_arg envp'nin 1 satiri.
 * @fn malloc(): t_env kadar yer aciyoruz.
 * @fn ft_split(): "HOME"="/Users/yuandre" -> "data[0]"="data[1]".
 * @return int 
 */
int	env_struct(t_base *base, char *new_arg)
{
	t_env	*new;
	t_env	*temp;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (ERROR);
	new->data = ft_split(new_arg, '=');
	new->next = NULL;
	if (base->env == NULL)
	{
		base->env = new;
		base->env->next = NULL;
	}
	else
	{
		temp = base->env;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}
