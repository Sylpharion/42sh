/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 10:01:57 by smassand          #+#    #+#             */
/*   Updated: 2017/01/31 18:44:22 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void		ft_opt_error(int error, char c)
{
	if (error == 1)
		ft_putstr_fd("env: option requires an argument -- u\n", 2);
	else if (error == 3 || error == 4)
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
	}
	ft_env_usage();
}

void		ft_opt_i(char ***env)
{
	ft_free_tab(env);
}

int			ft_opt_u(t_envcpy *e, char *arg)
{
	if (!arg)
	{
		ft_opt_error(1, 0);
		return (1);
	}
	else
		e->env_cpy = ft_env_unset(e->env_cpy, arg);
	return (0);
}

int			ft_opt(char *opt, int i)
{
	if (opt && ft_strlen(opt) > 2)
	{
		ft_opt_error(4, opt[i + 1]);
		return (1);
	}
	else
	{
		ft_opt_error(3, opt[1]);
		return (1);
	}
	return (0);
}
