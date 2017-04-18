/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:31:40 by smassand          #+#    #+#             */
/*   Updated: 2017/02/01 17:12:35 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int			ft_verif_env(char **env, char *str)
{
	int		i;

	i = 0;
	if (!env)
		return (1);
	while (env[i])
	{
		if (ft_keycmp(env[i], str) == 0)
			return (0);
		i++;
	}
	return (1);
}

char		**ft_env_unset(char **env, char *str)
{
	int		i;
	int		j;
	char	**update;

	if (!str || ft_verif_env(env, str) != 0)
		return (env);
	i = 0;
	j = 0;
	update = (char **)malloc(sizeof(char *) * ft_tablen(env));
	while (env[i])
	{
		if (ft_keycmp(env[i], str) == 0)
			i++;
		else
		{
			update[j] = ft_strdup(env[i]);
			i++;
			j++;
		}
	}
	update[j] = 0;
	ft_free_tab(&env);
	return (update);
}

int			ft_unset(t_envcpy *e, t_save *save)
{
	if (ft_opt_u(e, save->arg[e->i + 1]) == 1)
	{
		ft_free_env(e);
		*(save->exit_state) = 1;
		return (1);
	}
	e->i += 2;
	return (0);
}
