/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelauna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:39:05 by mdelauna          #+#    #+#             */
/*   Updated: 2017/01/31 13:14:05 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_add_name_heredoc(char *str, t_save *save)
{
	int		i;
	char	**tab;
	char	**tab_b;

	i = 0;
	tab_b = NULL;
	tab = ft_strsplit(str, '<');
	if (tab[1] != NULL)
		tab_b = ft_strsplit(tab[1], ' ');
	if (save->name_file)
		free(save->name_file);
	if (tab[1] != NULL)
		save->name_file = ft_strdup(ft_strtrim(tab_b[0]));
	else
		save->name_file = ft_strdup(ft_strtrim(tab[0]));
	ft_free_tab(&tab);
	ft_free_tab(&tab_b);
}

void	ft_init_name_param(t_save *save, char **tab, int j, char **tab_path)
{
	int		i;
	char	*sv;
	char	**tab_bis;

	i = -1;
	save->arg_param = ft_strsplit(tab[j], ' ');
	if (tab[j + 1])
	{
		tab_bis = ft_strsplit(tab[j + 1], ' ');
		save->name_file = ft_strdup(ft_strtrim(tab_bis[0]));
		ft_free_tab(&tab_bis);
	}
	else if (tab[1] && ft_strchr(tab[1], '>'))
	{
		free(save->name_file);
		save->name_file = ft_strtrim(*ft_strsplit(tab[1], '>'));
	}
	while (tab_path[++i])
	{
		sv = ft_strjoin(ft_strdup(tab_path[i]), "/");
		save->name_param = ft_strjoin_free(sv, save->arg_param[0], 1);
		if (access(save->name_param, F_OK | X_OK) == 0)
			return ;
		free(save->name_param);
	}
}
