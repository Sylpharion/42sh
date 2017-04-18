/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <smassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:28:28 by smassand          #+#    #+#             */
/*   Updated: 2017/02/05 19:10:29 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void		ft_var(t_envcpy *e, t_save *save)
{
	while (save->arg[e->i] && ft_strchr(save->arg[e->i], '='))
	{
		e->env_cpy = ft_env_set(e, save->arg[e->i]);
		e->i++;
	}
	ft_exec_env(e, save);
	ft_free_env(e);
}

static int	ft_ignore_env(t_envcpy *e)
{
	ft_opt_i(&e->env_cpy);
	e->env_cpy = NULL;
	e->i++;
	return (1);
}

static int	ft_check_opt(t_envcpy *e, t_save *save)
{
	if (ft_strcmp(save->arg[e->i], "-") == 0)
		ft_opt_i(&e->env_cpy);
	else if (ft_strcmp(save->arg[e->i], "--") == 0)
		save->use_env_tmp = NO;
	else if (ft_strcmp(save->arg[e->i], "--unset") == 0 ||
			ft_strcmp(save->arg[e->i], "-u") == 0)
	{
		if (save->arg[e->i + 1])
		{
			if (ft_verif_env(e->env_cpy, save->arg[e->i + 1]))
				save->use_env_tmp = NO;
		}
		return (ft_unset(e, save));
	}
	else if (ft_strcmp(save->arg[e->i], "--ignore-environement") == 0 ||
			ft_strcmp(save->arg[e->i], "-i") == 0)
		return (ft_ignore_env(e) & ft_free_env(e));
	else if (ft_opt(save->arg[e->i], 1) == 1)
	{
		ft_free_env(e);
		*(save->exit_state) = 1;
		return (1);
	}
	return (-1);
}

static void	ft_print_and_free_env(t_envcpy *e, t_save *save)
{
	ft_printenv(e->env_cpy, save);
	ft_free_env(e);
	*(save->exit_state) = 0;
	save->use_env_tmp = NO;
}

void		ft_env(t_save *save)
{
	t_envcpy	e;
	int			tmp;

	ft_init_env(&e, ft_cp_env_to_tab(save->builts->env), save);
	if (ft_tablen(save->arg) < 2 ||
			ft_strchr(save->arg_semicolon[save->semi_i], '>') ||
			ft_strchr(save->arg_semicolon[save->semi_i], '|'))
	{
		ft_print_and_free_env(&e, save);
		return ;
	}
	ft_parse_path(&e, save);
	while (save->arg[e.i] && save->arg[e.i][0] == '-')
	{
		save->use_env_tmp = YES;
		tmp = ft_check_opt(&e, save);
		if (tmp == 0)
			continue ;
		else if (tmp == 1)
			break ;
		e.i++;
	}
	ft_var(&e, save);
}
