/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_left_chevron.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:23:44 by afougere          #+#    #+#             */
/*   Updated: 2017/01/31 18:49:10 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_fork_back(t_save *save, t_list *lst, char **tab, int fd_bis)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	ft_stderr(save, "<<");
	if (pid == 0)
	{
		while (lst)
		{
			ft_putendl_fd(lst->content, fd[1]);
			lst = lst->next;
		}
	}
	else
	{
		wait(&pid);
		close(fd[1]);
		dup2(fd[0], 0);
		if (fd_bis > 0)
			dup2(fd_bis, 1);
		execve(save->name_param, tab, NULL);
		return (0);
	}
	return (1);
}

static int	ft_double_back_chevron_bis(t_save *save, t_list *lst, char **tab,
				int fd_bis)
{
	char	**sv;

	if (ft_strchr(save->tab_bis[0], '>'))
	{
		ft_free_tab(&tab);
		sv = ft_strsplit(save->tab_bis[0], '>');
		tab = ft_strsplit(sv[0], ' ');
	}
	else if (ft_strchr(save->tab_bis[0], '<'))
	{
		ft_free_tab(&tab);
		sv = ft_strsplit(save->tab_bis[0], '<');
		tab = ft_strsplit(sv[0], ' ');
	}
	if (ft_bultins_or_exec(tab, 0, save, fd_bis))
		return (1);
	if (!ft_fork_back(save, lst, tab, fd_bis))
		return (0);
	return (1);
}

static int	betwen_two_fonction(t_list **lst_bis, t_save *save, int fd_bis,
				char **tab)
{
	ft_list_reverse(lst_bis);
	ft_free_tab(&tab);
	tab = ft_strsplit(save->tab_bis[0], ' ');
	if (ft_double_back_chevron_bis(save, *lst_bis, tab, fd_bis))
	{
		ft_putendl("");
		return (1);
	}
	return (0);
}

static int	ft_infinite(t_save *save, int fd_bis, char **tab)
{
	while (1)
	{
		save->termio->yes = 1;
		save->termio->prompt_len = 2;
		save->termio->prompt = ft_strdup("? ");
		ft_term(save, save->termio);
		if ((save->termio->ctrl_d_heredoc &&
		!ft_strcmp(save->termio->ctrl_d_heredoc, save->name_file))
		|| !ft_strcmp(save->line, save->name_file))
			break ;
		if (ft_jj(-1) == 3)
			return (1);
		ft_lstadd(&save->lst_heredoc,
		ft_lstnew(save->line, ft_strlen(save->line) + 1));
		ft_putstr("\n? ");
	}
	if (save->termio->ctrl_d_heredoc && save->line && ft_strlen(save->line) > 0)
		ft_lstadd(&save->lst_heredoc,
		ft_lstnew(save->line, ft_strlen(save->line) + 1));
	if (betwen_two_fonction(&save->lst_heredoc, save, fd_bis, tab))
		return (1);
	return (0);
}

int			ft_double_back_chevron(t_save *save, char **tab_path, int fd_bis,
				char *str)
{
	char	**tab;

	tab = NULL;
	save->tab_bis = NULL;
	save->termio->heredoc = 1;
	save->lst_heredoc = NULL;
	if (ft_strchr(str, '|'))
	{
		save->tab_bis = ft_strsplit(str, '|');
		tab = ft_strsplit(save->tab_bis[0], '<');
	}
	else
	{
		tab = ft_strsplit(str, '<');
		save->tab_bis = ft_strsplit(str, '<');
	}
	ft_add_name_heredoc(str, save);
	ft_init_name_param(save, tab, 0, tab_path);
	ft_putstr("? ");
	if (ft_infinite(save, fd_bis, tab))
		return (1);
	return (0);
}
