/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_left_chevron.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:23:59 by afougere          #+#    #+#             */
/*   Updated: 2017/01/25 15:04:45 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	**ft_init_back_chev(t_save *save, char *str)
{
	size_t	len;
	char	*sv;
	char	**sp;
	char	**fc;

	len = 0;
	sp = NULL;
	while (str[len] != '<')
		len++;
	sv = ft_strsub(str, 0, len);
	sp = ft_strsplit(sv, ' ');
	ft_init_name_param(save, sp, 0, save->utils->path);
	save->tab_bis = ft_strsplit(str, '<');
	fc = ft_strsplit(save->tab_bis[1], ' ');
	save->name_file = ft_strdup(fc[0]);
	free(sv);
	return (sp);
}

int			ft_back_chevron(t_save *save, char *str, int fd_bis)
{
	char	**sp;
	int		fd;

	sp = ft_init_back_chev(save, str);
	fd = open(save->name_file, O_RDONLY);
	ft_stderr(save, "<");
	if (fd == -1 && ft_strcmp(save->name_file, "echo"))
	{
		ft_putstr_fd(save->termio->prompt, 2);
		ft_putstr_fd(" No such file or directory: ", 2);
		ft_putendl_fd(save->name_file, 2);
		return (1);
	}
	dup2(fd, 0);
	if (fd_bis > 0)
		dup2(fd_bis, 1);
	if (execve(save->name_param, sp, NULL) == -1)
		return (0);
	return (1);
}
