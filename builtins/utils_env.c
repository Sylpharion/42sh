/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 11:46:23 by afougere          #+#    #+#             */
/*   Updated: 2017/02/01 14:52:31 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char		*ft_getpath(char **env)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (env[i])
	{
		if (ft_keycmp(env[i], "PATH") == 0)
		{
			str = ft_strdup(&env[i][5]);
			break ;
		}
		i++;
	}
	return (str);
}

int			ft_free_env(t_envcpy *e)
{
	if (e->env_cpy)
		ft_free_tab(&e->env_cpy);
	if (e->path)
		ft_free_tab(&e->path);
	return (1);
}

void		ft_init_env(t_envcpy *e, char **env, t_save *save)
{
	e->arg_cpy = save->arg;
	e->env_cpy = env;
	e->arg_cpy = NULL;
	e->path = NULL;
	e->i = 1;
}

void		ft_parse_path(t_envcpy *e, t_save *save)
{
	char	*tmp;

	tmp = NULL;
	save->use_env_tmp = YES;
	if (ft_verif_env(e->env_cpy, "PATH") == 0)
	{
		tmp = ft_getpath(e->env_cpy);
		e->path = ft_strsplit(tmp, ':');
	}
	else
		e->path = ft_strsplit("./:/bin:/usr/bin", ':');
	if (tmp)
		free(tmp);
}
