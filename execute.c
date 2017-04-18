/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <ggobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 10:11:09 by ggobin            #+#    #+#             */
/*   Updated: 2017/01/31 18:47:51 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "operators.h"
#include "Auto_completion/auto.h"

static void		free_for_all(char *string, char **arg, char *sv)
{
	free(string);
	ft_free_tab(&arg);
	free(sv);
}

int				ft_test_acces(char **tab_path, t_save *save, char **envc, int i)
{
	char	*str;
	char	*sv;
	char	*string;
	char	**arg;

	str = ft_strjoin(tab_path[i], "/");
	sv = ft_strjoin_free(str, save->arg[0], 1);
	string = ft_split_stderr(save->arg, save, 0);
	arg = ft_strsplit(string, ' ');
	ft_stderr(save, (char*)1);
	if (access(sv, F_OK) == 0)
	{
		if (access(sv, X_OK) == 0)
			if (execve(sv, arg, envc) != -1)
			{
				free_for_all(string, arg, sv);
				return (1);
			}
		ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(save->arg[0], 2);
		return (1);
	}
	free_for_all(string, arg, sv);
	return (0);
}

void			ft_exec_com(t_save *save, int i)
{
	pid_t	pid;

	ft_get_path(save);
	if (save->fd == 1 && check_func(save))
		return ;
	if (save->fd == 3 && !ft_error_redirection(save->arg_semicolon[i]))
		return ;
	if (save->fd == 3 && ft_redir_and_bultins(save, i))
		;
	pid = fork();
	if (pid > 0)
		wait(save->exit_state);
	if (pid == 0)
	{
		if (!ft_do_exc(save, i, -1))
		{
			if (save->termio->yes == 2)
				ft_putchar('\n');
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(save->arg[0], 2);
			exit(127);
		}
		exit(0);
	}
}

static void		init_loop(t_save *save, int i)
{
	char *str;

	save->semi_i = i;
	save->arg = ft_strsplit(save->arg_semicolon[i], ' ');
	str = ft_strchr(save->arg_semicolon[i], '>');
	ft_change_tilde(&save->arg, save->builts->env);
	ft_change_dollar(&save->arg, &save->builts->env);
	if (ft_strchr(save->arg_semicolon[i], '|') ||
			ft_strchr(save->arg_semicolon[i], '<')
			|| (str && str + 1 && *(str + 1) != '&'))
		save->fd = 3;
}

void			loop(t_save *save, int i)
{
	if (save->fail_quotes == 1)
		return ;
	ft_parse_arg(&save);
	while (save->arg_semicolon[++i])
	{
		init_loop(save, i);
		if ((ft_strlen(save->line) > 0))
		{
			if (execute_if(*save->exit_state, save->last_operator))
				ft_exec_com(save, i);
		}
		save->fd = 1;
		if (save->arg)
			ft_free_tab(&save->arg);
		save->arg = NULL;
		if (!save->arg_semicolon)
			break ;
	}
	if (save->arg_semicolon)
		ft_free_tab(&save->arg_semicolon);
	save->arg_semicolon = NULL;
	save->last_operator = save->next_operator;
}
