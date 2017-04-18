/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 15:35:34 by afougere          #+#    #+#             */
/*   Updated: 2017/02/05 16:04:52 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/env.h"
#include "auto.h"

char		*ft_add_path(char *content, char **path, t_save *save)
{
	int		i;
	char	*tmp;

	(void)save;
	i = 0;
	tmp = NULL;
	if (!ft_strchr(content, '/') && content[0] != '.')
	{
		tmp = ft_strjoin("/", content);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
	}
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin_free(tmp, content, 1);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (ft_strdup(content));
}

static void	ft_aff_arg2(char *c, t_termio *termio, t_utils *utils, char *str)
{
	char	*tmp;

	tmp = ft_strsub(utils->save, 0, str - utils->save);
	termio->copy_for_lst = ft_strjoin_free(tmp, (char *)c, 1);
	termio->copy_for_lst = ft_strjoin_free(termio->copy_for_lst,
							utils->tree->content, 1);
}

void		ft_aff_arg(t_utils *utils, t_save *save, t_termio *termio)
{
	char *str;
	char *sl;
	char *sp;

	termio->copy_for_lst = NULL;
	if (!ft_strstr(utils->save, utils->tree->content))
	{
		sl = ft_strrchr(utils->save, '/');
		sp = ft_strrchr(utils->save, ' ');
		str = sl >= sp ? sl : sp;
		if (str && *str == '/')
			ft_aff_arg2("/", termio, utils, str);
		else if (str && *str == ' ')
			ft_aff_arg2(" ", termio, utils, str);
		else
			termio->copy_for_lst = ft_strdup((char *)utils->tree->content);
	}
	else
		termio->copy_for_lst = ft_strdup(utils->save);
	ft_lst_free((t_list **)(&termio->history->content));
	ft_str_to_lst((t_list **)(&termio->history->content),
	termio->copy_for_lst, save, termio);
	free(termio->copy_for_lst);
}

static void	ft_free_var_tabu(t_utils **utils)
{
	free((*utils)->save);
	if ((*utils)->aff_or_not == 1)
	{
		ft_free_tab(&(*utils)->path);
		ft_free_tree(&(*utils)->tree);
	}
}

int			ft_tab(t_utils *utils, t_save *save)
{
	static int i = 0;

	i++;
	utils->save = NULL;
	utils->tree = NULL;
	ft_get_path(save);
	ft_lst_to_str((t_list *)save->termio->history->content, save, save->termio);
	if (save->termio->history->content)
	{
		i = 0;
		utils->save = ft_tilde_str(save->line, save);
		ft_parse_cmd(utils);
		ft_many_or_one(utils, save);
	}
	else if (utils->aff_or_not == 1 && i == 2)
	{
		i = 0;
		ft_aff_all_exec(utils);
		write(1, "\n", 1);
		ft_putstr(save->termio->prompt);
	}
	ft_free_var_tabu(&utils);
	return (0);
}
