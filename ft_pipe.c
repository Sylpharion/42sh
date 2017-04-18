/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:27:10 by afougere          #+#    #+#             */
/*   Updated: 2017/01/31 13:13:07 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_pipe_bis(t_save *save, char **tab, int j, int fd_bis)
{
	if (tab[j + 1])
	{
		if (ft_strchr(tab[j + 1], '>'))
			return (ft_chevron(save, tab[j + 1], fd_bis));
		else if (tab[j + 2])
			ft_pipe(save, tab, save->utils->path, j + 1);
	}
	return (0);
}

int		ft_pipe(t_save *save, char **tab, char **tab_path, int j)
{
	int				i;
	extern char		**environ;

	save->pipe_struct->in = 0;
	i = 0;
	while (i < j - 1)
	{
		tab[i] = ft_strtrim(tab[i]);
		ft_init_name_param(save, tab, i, tab_path);
		pipe(save->pipe_struct->fd);
		ft_fork(tab, i, save);
		close(save->pipe_struct->fd[1]);
		save->pipe_struct->in = save->pipe_struct->fd[0];
		i++;
	}
	if (save->pipe_struct->in != 0)
		dup2(save->pipe_struct->in, 0);
	tab[i] = ft_strtrim(tab[i]);
	if (ft_strchr(tab[i], '>'))
		return (ft_chevron(save, tab[i], save->pipe_struct->in));
	ft_init_name_param(save, tab, i, tab_path);
	ft_stderr(save, "|");
	return (execve(save->name_param, save->arg_param, environ));
}

void	ft_check_setenv(char **tabb)
{
	int i;

	i = 0;
	while (tabb[i])
	{
		if (i == 0 && !ft_strcmp(tabb[i], "setenv") &&
		tabb[i + 1] && !ft_strcmp(tabb[i + 1], "|"))
		{
			free(tabb[i]);
			tabb[i] = ft_strdup("env");
		}
		i++;
	}
}

int		ft_split_pipe(t_save *save, int i, char **tab_path)
{
	char	**tab;
	char	*str;
	char	**tabb;

	save->pipe_struct = (t_pipe *)malloc(sizeof(t_pipe));
	if (ft_strrchr(save->arg_semicolon[i], '|'))
	{
		tabb = ft_strsplit(save->arg_semicolon[i], ' ');
		ft_check_setenv(tabb);
		str = ft_split_stderr(tabb, save, 0);
		tab = ft_strsplit(str, '|');
		i = 0;
		while (tab[i])
			i++;
		if (ft_pipe(save, tab, tab_path, i))
		{
			ft_free_tab(&tab);
			return (1);
		}
		ft_free_tab(&tab);
	}
	return (0);
}

int		ft_open_chev(t_save *save, int j)
{
	int		i;
	int		fd;
	char	*name_open;

	i = 0;
	name_open = NULL;
	while (save->arg[i])
	{
		if (!ft_strcmp(save->arg[i], ">") && ft_strcmp(save->arg[j - 1],
		"2>&1"))
		{
			name_open = ft_init_name_fd(save);
			fd = open(name_open, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			free(name_open);
			break ;
		}
		else if (!save->arg[i + 1] && ft_strcmp(save->arg[j - 1], "2>&1"))
		{
			name_open = ft_init_name_fd(save);
			fd = open(save->name_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			free(name_open);
		}
		i++;
	}
	return (fd);
}
