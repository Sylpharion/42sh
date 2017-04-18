/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 11:44:49 by afougere          #+#    #+#             */
/*   Updated: 2017/01/31 18:18:10 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void		ft_printenv(char **env, t_save *save)
{
	int		i;

	if (save->use_env_tmp == YES)
		env = save->env_tmp;
	if (ft_tablen(env) < 1)
		return ;
	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], save->fd);
		i++;
	}
}

int			ft_tablen(char **tab)
{
	int		i;

	i = 0;
	if (tab != NULL)
		while (tab[i])
			i++;
	return (i);
}

int			ft_keycmp(char *str, char *key)
{
	int		i;

	i = 0;
	while (str[i] != '=')
	{
		if (str[i] != key[i])
			return (1);
		i++;
	}
	return (0);
}

void		ft_exec_env(t_envcpy *e, t_save *save)
{
	if (!save->arg[e->i])
	{
		ft_printenv(e->env_cpy, save);
		ft_free_env(e);
		*(save->exit_state) = 0;
		return ;
	}
	else
	{
		save->env_tmp = e->env_cpy;
		e->env_cpy = NULL;
		free(save->line);
		save->line = ft_strdup(save->arg[e->i]);
		ft_free_env(e);
		*(save->exit_state) = -1;
		if (save->arg_semicolon)
			ft_free_tab(&save->arg_semicolon);
		if (save->arg)
			ft_free_tab(&save->arg);
		loop(save, -1);
		if (save->env_tmp)
			ft_free_tab(&save->env_tmp);
		save->env_tmp = NULL;
		return ;
	}
}

void		ft_get_env_lst(char **envp, t_builts *builts)
{
	int i;

	i = 0;
	builts->env = NULL;
	if (!envp[0])
		return ;
	while (envp[i])
	{
		ft_lstadd(&builts->env, ft_lstnew(envp[i], ft_strlen(envp[i]) + 1));
		i++;
	}
	ft_list_reverse(&builts->env);
}
