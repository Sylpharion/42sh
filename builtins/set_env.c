/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <ggobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 13:33:04 by ggobin            #+#    #+#             */
/*   Updated: 2017/02/06 14:02:37 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void		setup_update(t_update *u, t_envcpy *e, char *str)
{
	u->equals[0] = ft_strchr(e->env_cpy[u->i], '=');
	u->equals[0]++;
	u->c[0] = *(u->equals[0]);
	*(u->equals[0]) = 0;
	u->equals[1] = ft_strchr(str, '=');
	u->equals[1]++;
	u->c[1] = *(u->equals[1]);
	*(u->equals[1]) = 0;
}

int				make_update(t_envcpy *e, char *str, char **update)
{
	t_update	u;

	u.i = 0;
	while (e->env_cpy[u.i])
	{
		setup_update(&u, e, str);
		if (!ft_strcmp(e->env_cpy[u.i], str))
		{
			*(u.equals[1]) = u.c[1];
			*(u.equals[0]) = u.c[0];
			update[u.i] = ft_strdup(str);
		}
		else
		{
			*(u.equals[1]) = u.c[1];
			*(u.equals[0]) = u.c[0];
			update[u.i] = ft_strdup(e->env_cpy[u.i]);
		}
		u.i++;
	}
	return (u.i);
}

char			**ft_env_set(t_envcpy *e, char *str)
{
	char	**update;
	int		i;

	if (!str)
		return (e->env_cpy);
	if (ft_verif_env(e->env_cpy, str) == 0)
		update = (char **)malloc(sizeof(char *) * (ft_tablen(e->env_cpy) + 1));
	else
		update = (char **)malloc(sizeof(char *) * (ft_tablen(e->env_cpy) + 2));
	i = 0;
	if (e->env_cpy)
		i = make_update(e, str, update);
	if (ft_verif_env(e->env_cpy, str) == 0)
		update[i] = NULL;
	else
	{
		update[i] = ft_strdup(str);
		update[i + 1] = NULL;
	}
	ft_free_tab(&e->env_cpy);
	return (update);
}

void			change_env_shlvl(t_list **env, char *str)
{
	t_list *tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "SHLVL=", 6))
		{
			free(tmp->content);
			tmp->content = ft_strjoin("SHLVL=", str);
		}
		tmp = tmp->next;
	}
}
