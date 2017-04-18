/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_right_chevron.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:27:26 by afougere          #+#    #+#             */
/*   Updated: 2017/01/27 16:36:11 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	ft_error_soon(t_save *save)
{
	ft_putstr_fd(save->termio->prompt, 2);
	ft_putstr_fd(" command not found: ", 2);
	ft_putendl_fd(save->arg_param[0], 2);
	*save->exit_state = 1;
}

static int	ft_soon_chev(char **tab, t_save *save, int fd)
{
	char **bis;

	if (ft_strchr(tab[0], '<'))
		return (ft_chevron(save, tab[0], fd));
	if (ft_strchr(tab[1], '<'))
		return (ft_chevron(save, tab[1], fd));
	bis = ft_init_arg_chev(tab);
	if (access(save->name_param, F_OK | X_OK) == 0)
	{
		dup2(fd, 1);
		save->fd_chev = fd;
		if (ft_bultins_or_exec(tab, 0, save, fd) == 1)
			;
		else
		{
			execve(save->name_param, bis, NULL);
			return (0);
		}
	}
	else
		ft_error_soon(save);
	return (1);
}

int			ft_chevron_right(char **tab_path, char **tab, t_save *save, int j)
{
	pid_t	pid;
	int		fd;

	ft_init_name_param(save, tab, 0, tab_path);
	fd = ft_open_chev(save, j);
	if (ft_bultins_or_exec(tab, 0, save, fd))
		return (1);
	pid = fork();
	ft_stderr(save, ">");
	if (pid == 0)
	{
		if (!ft_soon_chev(tab, save, fd))
			return (0);
	}
	close(fd);
	if (pid > 0)
		wait(NULL);
	return (1);
}
