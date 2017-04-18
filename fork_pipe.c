/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <ggobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 10:24:33 by ggobin            #+#    #+#             */
/*   Updated: 2017/01/31 13:02:59 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	dup_them_all(t_save *save)
{
	if (save->pipe_struct->in != 0)
	{
		dup2(save->pipe_struct->in, 0);
		close(save->pipe_struct->in);
	}
	if (save->pipe_struct->out != 1)
	{
		save->stdout_dup = dup(1);
		dup2(save->pipe_struct->out, 1);
		close(save->pipe_struct->out);
	}
}

int			ft_fork(char **tab, int i, t_save *save)
{
	pid_t		pid;
	extern char	**environ;

	save->pipe_struct->out = save->pipe_struct->fd[1];
	ft_init_name_param(save, tab, i, save->utils->path);
	if ((pid = fork()) == 0)
	{
		dup_them_all(save);
		ft_stderr(save, (char *)"|");
		if (ft_strchr(tab[i], '<'))
		{
			ft_chevron(save, tab[i], save->pipe_struct->in);
			exit(0);
		}
		if (ft_bultins_or_exec(tab, i, save, save->pipe_struct->in))
			exit(0);
		return (execve(save->name_param, save->arg_param, environ));
	}
	if (pid > 0 && ft_strstr(save->line, (char *)"<<"))
		wait(NULL);
	return (pid);
}
