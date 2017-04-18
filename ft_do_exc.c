/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_exc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelauna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 18:43:42 by mdelauna          #+#    #+#             */
/*   Updated: 2017/01/31 19:03:20 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "operators.h"
#include "Auto_completion/auto.h"

static int		free_data(t_save *save, char ***envc)
{
	ft_free_tab(&save->utils->path);
	ft_free_tab(envc);
	return (1);
}

static int		exec_local(t_save *save, char **envc)
{
	char	*cmd;

	if (access(save->arg[0], F_OK) == 0 &&
			(ft_strncmp(save->arg[0], "./", 2) == 0 ||
				save->arg[0][0] == '/'))
	{
		cmd = save->arg[0][0] == '/' ? save->arg[0] : &save->arg[0][2];
		if (access(cmd, X_OK) == 0)
		{
			if (execve(save->arg[0], save->arg, envc) != -1)
			{
				ft_free_tab(&envc);
				return (1);
			}
		}
		ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(save->arg[0], 2);
		return (1);
	}
	return (0);
}

static void		mr_proper(t_save *save, char ***envc)
{
	ft_free_tab(&save->utils->path);
	ft_free_tab(envc);
	if (ft_strcmp(save->arg[0], "<<") == 0)
		exit(0);
}

int				ft_do_exc(t_save *save, int j, int i)
{
	char	**envc;

	if (ft_split_pipe(save, j, save->utils->path))
		return (1);
	if (ft_chevron(save, save->arg_semicolon[j], 0))
		return (1);
	ft_stderr(save, NULL);
	envc = save->use_env_tmp == YES ? save->env_tmp : ft_envc(save);
	if (exec_local(save, envc))
		return (1);
	if (!save->utils->path)
	{
		mr_proper(save, &envc);
		return (0);
	}
	while (save->utils->path[++i])
	{
		if (ft_test_acces(save->utils->path, save, envc, i))
			return (free_data(save, &envc));
	}
	mr_proper(save, &envc);
	return (0);
}
