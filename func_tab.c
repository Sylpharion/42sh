/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:26:31 by afougere          #+#    #+#             */
/*   Updated: 2017/01/27 15:47:58 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtins/env.h"

void		ft_exit(t_save *save)
{
	int j;
	int i;

	j = 0;
	i = 0;
	while (save->arg[i])
		i++;
	if (save->arg[1])
	{
		while (save->arg[1][j])
		{
			if (i > 2 || ft_isalpha(save->arg[1][j]))
			{
				ft_putendl("exit: Expression Syntax.");
				return ;
			}
			j++;
		}
	}
	ft_putendl("exit");
	exit(0);
}

static char	**set_tab(void)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * 9);
	tab[0] = ft_strdup("env");
	tab[1] = ft_strdup("setenv");
	tab[2] = ft_strdup("export");
	tab[3] = ft_strdup("unsetenv");
	tab[4] = ft_strdup("unset");
	tab[5] = ft_strdup("cd");
	tab[6] = ft_strdup("exit");
	tab[7] = ft_strdup("echo");
	tab[8] = NULL;
	return (tab);
}

static t_f	*set_func(void)
{
	t_f	*ptr;

	ptr = (t_f *)malloc(sizeof(t_f) * 9);
	ptr[0] = ft_env;
	ptr[1] = ft_setenv;
	ptr[2] = ft_setenv;
	ptr[3] = ft_unsetenv;
	ptr[4] = ft_unsetenv;
	ptr[5] = ft_cd;
	ptr[6] = ft_exit;
	ptr[7] = ft_echo;
	ptr[8] = NULL;
	return (ptr);
}

int			check_func(t_save *save)
{
	char		**tab;
	t_f			*ptr;
	int			i;

	i = 0;
	tab = set_tab();
	ptr = set_func();
	while (tab[i])
	{
		if (save->arg[0] && !(ft_strcmp(tab[i], save->arg[0])))
		{
			ptr[i](save);
			ft_free_tab(&tab);
			free(ptr);
			return (1);
		}
		i++;
	}
	ft_free_tab(&tab);
	free(ptr);
	return (0);
}

void		ft_change_shlvl(t_save *save)
{
	char	*sh;
	int		nb;

	if ((sh = ft_getenv("SHLVL", save->builts->env)) == NULL)
	{
		ft_free_tab(&save->arg);
		ft_lstadd(&save->builts->env, ft_lstnew("SHLVL=1", 8));
	}
	else
	{
		nb = ft_atoi(sh);
		nb += 1;
		sh = ft_itoa(nb);
		change_env_shlvl(&save->builts->env, sh);
		free(sh);
	}
}
