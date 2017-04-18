/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 13:46:35 by afougere          #+#    #+#             */
/*   Updated: 2017/01/26 14:03:42 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtins/env.h"

int			ft_back_double_back(char **tab, char *tab_bis, t_save *save, int fd)
{
	int i;

	i = 0;
	while (tab_bis[i])
	{
		if (tab_bis[i] == '<' && tab_bis[i + 1] == '<')
			return (ft_double_back_chevron(save, save->utils->path, fd,
			tab_bis));
		else if (tab_bis[i] == '<' && tab_bis[i + 1] != '<')
		{
			if (ft_bultins_or_exec(tab, 0, save, 0))
				return (1);
			return (ft_back_chevron(save, tab_bis, fd));
		}
		i++;
	}
	return (0);
}

static int	ft_bultins_or_exec_bis(char **tab, int j)
{
	if ((!ft_strcmp(*ft_strsplit(tab[j], ' '), "setenv")))
		return (1);
	else if ((!ft_strcmp(*ft_strsplit(tab[j], ' '), "unsetenv")))
		return (1);
	return (0);
}

int			ft_bultins_or_exec(char **tab, int j, t_save *save, int fd)
{
	tab[j] = ft_strtrim(tab[j]);
	if (!ft_strcmp("echo", *ft_strsplit(tab[j], ' ')))
	{
		save->fd = 1;
		if (save->stder_bis && save->stdout_dup != -1)
			save->fd = save->stdout_dup;
		else if (ft_strchr(save->arg_semicolon[save->semi_i], '>') &&
							!ft_strchr(save->arg_semicolon[save->semi_i], '|'))
			save->fd = fd;
		ft_echo(save);
		return (1);
	}
	else if (!ft_strcmp("env", tab[j]))
	{
		save->fd = 1;
		if (fd > 0)
			save->fd = fd;
		ft_env(save);
		return (1);
	}
	else if (ft_bultins_or_exec_bis(tab, j))
		return (1);
	return (0);
}

char		**ft_init_arg_chev(char **tab)
{
	char **bis;
	char *str;

	bis = NULL;
	if (ft_strchr(ft_strtrim(tab[1]), ' '))
		str = ft_strjoin(tab[0], ft_strchr(ft_strtrim(tab[1]), ' '));
	else
		str = ft_strdup(tab[0]);
	bis = ft_strsplit(str, ' ');
	return (bis);
}

char		*ft_init_name_fd(t_save *save)
{
	char	*str;
	char	*pwd;

	if (save->name_file[0] == '~')
	{
		str = ft_strchr(save->name_file, '~') + 1;
		pwd = ft_strjoin(getenv("HOME"), str);
	}
	else if (save->name_file[0] != '/')
	{
		str = ft_strdup(save->name_file);
		pwd = getcwd(NULL, 0);
		pwd = ft_strjoin_free(pwd, "/", 1);
		pwd = ft_strjoin_free(pwd, save->name_file, 1);
	}
	else
		pwd = ft_strdup(save->name_file);
	return (pwd);
}
