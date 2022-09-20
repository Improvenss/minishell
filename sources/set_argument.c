/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_argument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 02:48:55 by gsever            #+#    #+#             */
/*   Updated: 2022/09/20 14:18:01 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	login_print(void)
{
	char	*name;

	name = env_findret("NAME");
	if (name == NULL)
		name = "42kocaeli.com.tr";
	printf(GREEN"\nLOGIN INFORMATION: "RED"%s%s%s\n"END, \
		env_findret("LOGNAME"), "@", name);
	printf("%s\n", GREEN"                _           _          "RED_BLINK
		"__  __  ______  __      __ ");
	printf("%s\n", GREEN"   ____ ___    (_) ____    (_) "BLACK"_____  "RED_BLINK
		"/ / / / / ____/ / /     / / ");
	printf("%s\n", GREEN"  / __ `__ \\  / / / __ \\  / / "BLACK"/ ___/ "RED_BLINK
		"/ /_/ / / __/   / /     / /  ");
	printf("%s\n", GREEN" / / / / / / / / / / / / / / "BLACK"(__  ) "RED_BLINK
		"/ __  / / /___  / /___  / /___");
	printf("%s\n", GREEN"/_/ /_/ /_/ /_/ /_/ /_/ /_/ "BLACK"/____/ "RED_BLINK
		"/_/ /_/ /_____/ /_____/ /_____/"END);
	printf("\n");
}

/**
 * @brief environ'u bul ve return et.
 * 
 * env_name PWD,HOME,OLDPWD... argümanları tutmaktadır.
 * 	If koşulu ile data[0] stringi strcmp ile
 * 	karşılaştırılır ve eşit ise 0 döner.
 * 
 * @param env_name 
 * @return char* 
 */
char	*env_findret(char *env_name)
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
 * @brief env yapısını listeye atamak için oluşturulmuş fonksiyon.
 * 
 * @param env_arg 
 */
void	env_struct(char *env_arg)
{
	t_env	*new;
	t_env	*temp;

	new = (t_env *)malloc(sizeof(t_env));
	new->data = ft_split(env_arg, '=');
	new->next = NULL;
	if (g_main.env == NULL)
	{
		g_main.env = new;
		g_main.env->next = NULL;
	}
	else
	{
		temp = g_main.env;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

/**
 * @brief 
 * 
 * env argümanları tek tek çağırılıp, listeye aktarılacak.
 * 	getenv("PATH"); gibi çağırılacak.
 */
void	set_argument(void)
{
	extern char	**environ;
	int			i;

	i = -1;
	g_main.env = NULL;
	while (environ[++i])
		env_struct(environ[i]);
	g_main.PATH = ft_split(env_findret("PATH"), ':');
	g_main.echo_val = 0;
	login_print();
}
