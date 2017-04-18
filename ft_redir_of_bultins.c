/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_of_bultins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:25:27 by afougere          #+#    #+#             */
/*   Updated: 2017/01/31 12:32:36 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtins/env.h"

int			ft_search_redir(t_save *save, int i, int nb, char *str)
{
	while (save->arg[i] && (!ft_strchr(save->arg[i], '|') &&
	!ft_strchr(save->arg[i], '<')))
		i++;
	if (save->arg[i] && (ft_strchr(save->arg[i], '|') ||
	ft_strchr(save->arg[i], '<')))
	{
		nb++;
		i++;
	}
	if (save->arg[i] && ft_strcmp(save->arg[i], str))
		ft_search_redir(save, i, nb, str);
	else
		i++;
	if (nb > 0)
		return (i);
	return (1);
}

static char	**ft_tab_redir_and_bultins(t_save *save, int nb)
{
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;
	while (save->arg[i])
	{
		if (!ft_strcmp(save->arg[i], "|"))
		{
			tab = ft_strsplit(save->arg_semicolon[nb], '|');
			break ;
		}
		else if (!ft_strcmp(save->arg[i], ">"))
		{
			tab = ft_strsplit(save->arg_semicolon[nb], '>');
			break ;
		}
		else if (!ft_strncmp(save->arg[i], "<", 1))
		{
			tab = ft_strsplit(save->arg_semicolon[nb], '<');
			break ;
		}
		i++;
	}
	return (tab);
}

static int	ft_setenv_unsetenv(char **tab, t_save *save, char **tb, int i)
{
	if (tab[i] && !ft_strchr(save->arg_semicolon[save->semi_i], '|') &&
	(!ft_strcmp(tb[0], "setenv") && (!tab[i - 1] || !tab[i + 1])))
	{
		ft_free_tab(&tb);
		ft_free_tab(&tab);
		ft_setenv(save);
		return (1);
	}
	if (tab[i] && !ft_strchr(save->arg_semicolon[save->semi_i], '|') &&
	(!ft_strcmp(tb[0], "unsetenv") && (!tab[i - 1] || !tab[i + 1])))
	{
		ft_free_tab(&tb);
		ft_free_tab(&tab);
		ft_unsetenv(save);
		return (1);
	}
	return (0);
}

int			ft_redir_and_bultins(t_save *save, int nb)
{
	char	**tab;
	int		i;
	char	**tb;

	i = -1;
	tab = ft_tab_redir_and_bultins(save, nb);
	while (tab && tab[++i])
	{
		tb = ft_strsplit(tab[i], ' ');
		if (ft_setenv_unsetenv(tab, save, tb, i))
			return (1);
		ft_free_tab(&tb);
	}
	ft_free_tab(&tab);
	return (0);
}
