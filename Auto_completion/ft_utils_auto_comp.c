/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_auto_comp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <ggobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:37:07 by ggobin            #+#    #+#             */
/*   Updated: 2017/01/25 18:42:21 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"
#include "../builtins/env.h"
#include "../globing/globing.h"

void		ft_get_path(t_save *save)
{
	char	*save_b;

	if (save->utils->path)
		ft_free_tab(&save->utils->path);
	save->utils->path = NULL;
	if (ft_getenv("PATH", save->builts->env))
	{
		save_b = ft_strdup(ft_getenv("PATH", save->builts->env));
		save->utils->path = ft_strsplit(save_b, ':');
		free(save_b);
	}
}

void		ft_readdir(t_utils *utils, char *name_open, char *name_file)
{
	struct dirent	*dirent;

	if ((utils->dir = opendir(name_open)))
	{
		while ((dirent = readdir(utils->dir)))
		{
			if ((!name_file || !ft_strncmp(name_file, dirent->d_name,
			ft_strlen(name_file)) || ft_glob(utils->glob, dirent->d_name)) &&
			(ft_strncmp(dirent->d_name, ".", 1)))
			{
				if ((int)ft_strlen(dirent->d_name) > utils->info_col->long_word)
					utils->info_col->long_word = ft_strlen(dirent->d_name);
				ft_add_node(dirent->d_name, &utils->tree, ft_strcmp);
				utils->nb_words++;
			}
		}
		closedir(utils->dir);
	}
	if (name_file)
	{
		if (!utils->nb_words && (ft_strchr(name_file, '*') ||
		ft_strchr(name_file, '[') || ft_strchr(name_file, '?')))
			ft_add_node(name_file, &utils->tree, ft_strcmp);
	}
}

static int	ft_ceil(double i)
{
	if (i != (double)((int)i))
		return ((int)i + 1);
	return ((int)i);
}

void		ft_cal_col(t_utils *utils)
{
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	utils->info_col->lg_col = utils->info_col->long_word + 2;
	utils->info_col->nb_col = ws.ws_col / utils->info_col->lg_col;
	utils->info_col->nb_line =
	ft_ceil(utils->nb_words / (double)utils->info_col->nb_col);
}

void		ft_backup_and_free(t_utils **utils, char *pwd, int i)
{
	char	*backup;

	backup = NULL;
	backup = ft_no_begin_slash(pwd, *utils, i, backup);
	if ((*utils)->glob.free_o_n == 1 || (*utils)->glob.free_o_n == 3)
		free((*utils)->glob.fmt);
	if ((*utils)->glob.free_o_n == 2 || (*utils)->glob.free_o_n == 3)
		free(backup);
}
