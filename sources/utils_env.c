/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:03:34 by akaraca           #+#    #+#             */
/*   Updated: 2022/10/15 22:03:34 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils_env.c
 * @author Ahmet KARACA (akaraca)
 * @author Gorkem SEVER (gsever)
 * @brief 
 * @version 0.1
 * @date 2022-08-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../includes/minishell.h"

int	env_strlen(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*env_data(t_env *tmp)
{
	char	*new;
	char	*del;

	new = ft_strdup(tmp->data[0]);
	if (tmp->is_env_equal == true)
	{
		del = new;
		new = ft_strjoin(new, "=");
		free(del);
	}
	if (tmp->data[1] != NULL)
	{
		del = new;
		new = ft_strjoin(new, tmp->data[1]);
		free(del);
	}
	return (new);
}

char	**env_be_char(t_env *env)
{
	char	**new;
	t_env	*tmp;
	int		size;
	int		i;

	i = 0;
	size = env_strlen(env);
	new = (char **)malloc(sizeof(char *) * size);
	tmp = env;
	while (tmp != NULL)
	{
		char *del = env_data(tmp);
		new[i] = del;
		free(del);
		i++;
		tmp = tmp->next;
	}
	new[i] = NULL;
	return (new);
}

/** OK:
 * @brief Environmentlerin icinde disaridan verdigimiz variable ve valuesini
 *  ariyoruz; eger varsa true donuyor, yoksa(bulamazsa) false donuyor.
 * 
 * @param base For base->env
 * @param env_var env -> [HERE]=not_here
 * @param value env -> [not_here]=[HERE]
 * @return If variable found OK: true. Not found NOK: false.
 */
bool	env_is_have(t_base *base, char *env_var, char *value)
{
	t_env	*tmp;

	tmp = base->env;
	while(tmp)
	{
		if (ft_strncmp(tmp->data[0], env_var, ft_strlen(env_var)) == 0
			&& ft_strncmp(tmp->data[1], value, ft_strlen(value)) == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

/**
 * @brief Set the env object
 * 
 * @param base 
 * @param env_name 
 * @param new_str 
 * @note int exit; kullanilmiyor.
 */
void	set_env(t_base *base, char *env_name, char *new_str)
{
	t_env	*tmp;
	char	*del;
	bool	status;

	tmp = base->env;
	status = false; 
	while (tmp != NULL)
	{
		if (ft_strcmp_edited(env_name, tmp->data[0]) == 0)
		{
			status = true;
			del = tmp->data[1];
			if (new_str != NULL)
				tmp->data[1] = ft_strdup(new_str);
			else
				tmp->data[1] = NULL;
			free(new_str);
			free(del);
			break;
		}
		tmp = tmp->next;
	}
	if (status == false)
		free(new_str);
}

char	*env_findret(t_base *base, char *env_name)
{
	t_env	*tmp;

	tmp = base->env;
	while (tmp != NULL)
	{
		if (ft_strcmp_edited(env_name, tmp->data[0]) == 0)
		{
			if (tmp->data[1] != NULL)
			{
				return (ft_strdup(tmp->data[1]));
			}
			else
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*find_chr_ret_str(char *str, char c, bool status)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			break;
	}
	if (status == true)
	{
		if (str[i] == '\0')
			return (NULL);
		else
			return (ft_substr(str, i + 1, ft_strlen(str)));
	}
	return (ft_substr(str, 0, i));
}

int	env_size(char *src)
{
	char	*data_1;
	char	*data_2;

	data_1 = find_chr_ret_str(src, '=', false);
	data_2 = find_chr_ret_str(src, '=', true);
	if (data_2 == NULL)
	{
		free(data_1);
		return (1);
	}
	else if (data_1 && data_2)
	{
		free(data_1);
		free(data_2);
		return (2);
	}
	return (0);
}

char	**env_split(char *src)
{
	char	**dst;

	dst = NULL;
	dst = (char **)malloc(sizeof(char *) * (3));
	if (!dst)
	{
		print_error(SHELLNAME, NULL, NULL, strerror(ENOMEM));
		return(NULL);
	}
	dst[0] = find_chr_ret_str(src, '=', false);
	dst[1] = find_chr_ret_str(src, '=', true);
	dst[2] = NULL;
	return (dst);
}

/**
 * @brief base->env structu bossa yeni olusturulacak(ilk baslangictaki init),
 *  varsa yeni eklenecek env'yi sondaki linked-list'e ekleyecek.
 * 
 * @param base base->env structu icin.
 * @param new_arg Disaridan ekleyecegimiz env.
 * @fn malloc(): environment struct'u(env'nin 1 satiri icin) yer aciyoruz.
 * @fn ft_strncmp(): Yeni eklenecek env'da '=' varsa ture yapacagiz.
 * @fn ft_split(): env'nin ='in sol tarafi ve sag tarafi olacak sekilde,
 *  ayiriyoruz, data[0]=data[1] oluyor.
 * @return int OK: 0, NOK: ERROR
 */
int	env_struct(t_base *base, char *new_arg)
{
	t_env	*new;
	t_env	*temp;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (ERROR);
	new->is_env_equal = false;
	if (ft_strncmp(new_arg, "=", 1))
		new->is_env_equal = true;
	new->data = env_split(new_arg);
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

char	*env_findret_no_dup(t_base *base, char *env_name)
{
	t_env	*tmp;

	tmp = base->env;
	while (tmp != NULL)
	{
		if (ft_strcmp_edited(env_name, tmp->data[0]) == 0)
		{
			if (tmp->data[1] != NULL)
				return (tmp->data[1]);
			else
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}