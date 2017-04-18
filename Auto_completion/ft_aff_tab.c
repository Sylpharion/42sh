/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 11:38:33 by afougere          #+#    #+#             */
/*   Updated: 2017/02/02 17:06:19 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"
#include "../globing/globing.h"

int			ft_aff_all_exec(t_utils *utils)
{
	int		i;

	i = 0;
	while (utils->path && utils->path[i])
	{
		ft_readdir(utils, utils->path[i], NULL);
		i++;
	}
	if (utils->aff_or_not == 1)
	{
		write(1, "\n", 1);
		ft_read_tree(utils->tree, utils);
	}
	return (0);
}

static void	ft_list_cmd_path(t_utils *utils)
{
	int		i;

	i = 0;
	while (utils->path && utils->path[i])
	{
		utils->glob.fmt = NULL;
		ft_readdir(utils, utils->path[i], utils->save);
		i++;
	}
}

void		ft_parse_cmd(t_utils *utils)
{
	if (ft_strchr(utils->save, ' '))
	{
		ft_list_cmd_space(utils);
		if (utils->nb_words > 1 && utils->aff_or_not == 1)
		{
			write(1, "\n", 1);
			ft_read_tree(utils->tree, utils);
		}
		return ;
	}
	else
	{
		ft_list_cmd_path(utils);
		if (utils->nb_words > 1 && utils->aff_or_not == 1)
		{
			write(1, "\n", 1);
			ft_read_tree(utils->tree, utils);
		}
	}
}

void		ft_many_or_one(t_utils *utils, t_save *save)
{
	if (utils->nb_words > 1 && utils->aff_or_not == 1)
	{
		write(1, "\n", 1);
		ft_putstr(save->termio->prompt);
		ft_putstr(save->line);
	}
	else if (utils->nb_words == 1)
		ft_aff_arg(utils, save, save->termio);
}
