/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 21:52:55 by gsever            #+#    #+#             */
/*   Updated: 2022/10/04 12:47:56 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*clear_slash(t_base *base, char *str)
{
	char		*tmp;
	size_t		i;
	size_t		l;

	tmp = (char *)malloc(sizeof(char) * ft_strlen(str));
	if(!tmp)
		return (NULL);
	l = 0;
	if (!ft_strncmp_edited(env_findret("PWD=", base), "/", 1))
		tmp[l++] = '/';
	i = 0;
	while (l <= ft_strlen(str) && str[i] != '/')
		tmp[l++] = str[i++];
	tmp[l] = '\0';
	return (tmp);
}

char	*cd_slash(char *str)
{
	int		i;
	int		l;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * ft_strlen(str));
	if (!tmp)
		return (NULL);
	i = 0;
	l = 0;
	while (str[i] == '/')
		i++;
	if (str[i] == '\0')
		tmp[l++] = '/';
	while (str[i])
	{
		if (str[i - 1] == '/' && str[i] != '\0')
			tmp[l++] = '/';
		tmp[l++] = str[i++];
		while (str[i] == '/')
			i++;
	}
	tmp[l] = '\0';
	return (tmp);
}

char	*delete_front_slash(char *str)
{
	char	*tmp;
	int		l;
	int		i;

	l = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * l);
	while (str[l] != '/')
		l--;
	i = -1;
	while (++i < l)
		tmp[i] = str[i];
	if (l == 0)
		tmp[i++] = '/';
	tmp[i] = '\0';
	return (tmp);
}

int	file_or_directory_search(char *str, int x)
{
	int	fd;

	fd = open(str, x);
	close(fd);
	if (fd == -1)
		return (0);
	return (1);
}

void	set_env(t_base *base, char *env_name, char *new_str)
{
	int	i;
	int	k;
	int	l;

	i = -1;
	k = -1;
	l = -1;
	while (base->environ[++i])
	{
		if (ft_strncmp_edited(env_name, base->environ[i], ft_strlen(env_name)))
		{
			base->environ[i] = (char *)malloc(sizeof(char) * (ft_strlen(env_name)
				+ ft_strlen(new_str) + 1));
			while (env_name[++k])
				base->environ[i][k] = env_name[k];
			base->environ[i][k++] = '=';
			while (new_str[++l])
				base->environ[i][k++] = new_str[l];
			base->environ[i][k] = '\0';
			break ;
		}
	}
}

int	cmd_cd(t_base *base)
{
	if (base->array_line[1] == NULL
		|| ft_strncmp_edited(base->array_line[1], "~", 1)
		|| ft_strncmp_edited(base->array_line[1], "--", 2))
	{
		set_env(base, "OLDPWD", env_findret("PWD=", base));
		set_env(base, "PWD", env_findret("HOME=", base));
		chdir(env_findret("HOME=", base));
	}
	else if (ft_strncmp_edited(base->array_line[1], "-", 1))
	{
		base->cd_tmp = env_findret("OLDPWD=", base);
		set_env(base, "OLDPWD", env_findret("PWD=", base));
		set_env(base, "PWD", base->cd_tmp);
		chdir(base->cd_tmp);
	}
	else if (base->array_line[1] != NULL && file_or_directory_search(base->array_line[1], O_DIRECTORY))
	{
		set_env(base, "OLDPWD", env_findret("PWD=", base));
		if (ft_strncmp_edited(base->array_line[1], "..", 2))
			set_env(base, "PWD", delete_front_slash(env_findret("PWD=", base)));
		else if (base->array_line[1][0] == '/')
			set_env(base, "PWD", cd_slash(base->array_line[1]));
		else if (!ft_strncmp_edited(base->array_line[1], ".", 1))
		{
			base->cd_tmp = clear_slash(base, base->array_line[1]);
			set_env(base, "PWD", ft_strjoin(env_findret("PWD=", base), base->cd_tmp));
		}
		chdir(env_findret("PWD=", base));
	}
	else if (file_or_directory_search(base->array_line[1], 0))
		print_error("cd", base->array_line[1], NULL,"Not a directory");
	else
		print_error("cd", base->array_line[1], NULL, "No such file or directory");
	return (0);
}