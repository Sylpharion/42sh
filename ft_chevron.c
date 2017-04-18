/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chevron.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 16:31:58 by afougere          #+#    #+#             */
/*   Updated: 2017/01/26 13:48:07 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_init_sv_chev(char **tab, t_save *save, char *str, int fd)
{
	char	**tabb;

	tabb = ft_strsplit(tab[1], '<');
	if (!save->sv)
		save->sv = ft_strjoin(tab[0], "<");
	else
		save->sv = ft_strjoin_free(tab[0], "<", 1);
	save->sv = ft_strjoin_free(save->sv, tabb[1], 1);
	ft_free_tab(&tabb);
	tabb = ft_strsplit(str, '<');
	ft_free_tab(&tab);
	tab = ft_strsplit(tabb[0], '>');
	save->sv = ft_strjoin_free(save->sv, " >", 1);
	save->sv = ft_strjoin_free(save->sv, tab[1], 1);
	return (ft_chevron(save, save->sv, fd));
}

static int	ft_parse(char **tab, t_save *save, char *str, int fd)
{
	int j;

	j = 0;
	ft_free_tab(&tab);
	tab = ft_strsplit(str, '>');
	if (ft_strchr(tab[1], '<') &&
	*(ft_strchr(tab[1], '<') + 1) != '<')
		if (ft_init_sv_chev(tab, save, str, fd))
			return (1);
	while (save->arg[j])
		j++;
	if (ft_strchr(str, '>') &&
	ft_chevron_right(save->utils->path, tab, save, j))
		return (1);
	return (0);
}

int			ft_chevron(t_save *save, char *tab_bis, int fd)
{
	int		i;
	char	**tab;
	char	*str;

	i = -1;
	if (save->sv)
	{
		free(save->sv);
		save->sv = NULL;
	}
	tab = ft_strsplit(tab_bis, ' ');
	while (tab[++i])
	{
		if (ft_strchr(tab[i], '>'))
		{
			str = ft_split_stderr(ft_strsplit(tab_bis, ' '), save, 0);
			if (ft_strchr(str, '>'))
				if (ft_parse(tab, save, str, fd))
					return (1);
		}
	}
	if (ft_back_double_back(tab, tab_bis, save, fd))
		return (1);
	ft_free_tab(&tab);
	return (0);
}
