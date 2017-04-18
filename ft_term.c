/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 15:55:49 by afougere          #+#    #+#             */
/*   Updated: 2017/02/01 16:13:59 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "Auto_completion/auto.h"

void		ft_lst_to_str(t_list *list, t_save *save, t_termio *termio)
{
	int size;

	(void)termio;
	if (list && list->prev)
	{
		while (list->prev)
			list = list->prev;
	}
	size = ft_list_size(list);
	if (save->line)
		free(save->line);
	save->line = ft_memalloc(size + 1);
	size--;
	while (list && size >= 0)
	{
		save->line[size] = *(char*)list->content;
		list = list->next;
		size--;
	}
}

void		ft_home_end(t_list **lst, t_termio *termio, char buf)
{
	struct winsize ws;

	ioctl(0, TIOCGWINSZ, &ws);
	if (buf == 72)
	{
		while (termio->i > termio->prompt_len)
		{
			tputs(tgetstr("le", NULL), 1, outc);
			termio->i--;
			if ((*lst)->next)
				*lst = (*lst)->next;
		}
		return ;
	}
	while (termio->i < termio->size)
	{
		if (termio->i % ws.ws_col == ws.ws_col - 1)
			tputs(tgetstr("do", NULL), 1, outc);
		else
			tputs(tgetstr("nd", NULL), 1, outc);
		termio->i++;
		if ((*lst)->prev)
			*lst = (*lst)->prev;
	}
}

static int	ft_glob_or_not(t_save *save)
{
	if (ft_strchr(save->line, '*') || ft_strchr(save->line, '[')
	|| ft_strchr(save->line, ']') || (ft_strchr(save->line, '?') &&
	!ft_strstr(save->line, "$?")))
		return (1);
	return (0);
}

void		ft_enter_and_glob(t_save *save, t_termio *termio, char *cp)
{
	char	*end;

	end = NULL;
	ft_lst_to_str(((t_list *)termio->history->content), save, termio);
	if (ft_glob_or_not(save))
	{
		init_glob(&end, &cp, save);
		ft_tree_to_str(save->utils->tree, save);
		if (end)
		{
			save->line = ft_strjoin_free(save->line, (char *)" ", 1);
			save->line = ft_strjoin_free(save->line, end, 3);
		}
		ft_free_tree(&save->utils->tree);
		if (termio->history_save)
		{
			ft_lst_free((t_list **)(&termio->history->content));
			termio->history->content =
			ft_cp_env_to_sv((t_list **)(&termio->history_save->content));
			ft_lst_free((t_list **)(&termio->history_save->content));
			ft_lst_free(&termio->history_save);
		}
		ft_free_tab(&save->utils->path);
	}
}

int			ft_puts_goto(t_termio *termio, t_save *save)
{
	struct winsize	ws;
	t_list			*sv;

	termio->size = termio->prompt_len;
	termio->i = termio->prompt_len;
	ioctl(0, TIOCGWINSZ, &ws);
	ft_lstadd(&termio->history, ft_lstnew(NULL, 0));
	sv = termio->history;
	while (1)
	{
		ft_init_var_save(&save);
		ft_bzero(termio->buffer, sizeof(termio->buffer));
		read(0, termio->buffer, 1024);
		if (ft_ctrl_d(termio->buffer, termio, save) == 2)
			return (0);
		ft_word_cut_copy_term(termio->buffer, termio, save);
		ft_save_history(termio, save, termio->buffer);
		ft_put_buffer(termio->buffer, termio, save);
		termio->history_save = NULL;
		if (!ft_puts_goto_bis(termio->buffer, termio, sv, save))
			return (0);
	}
	return (1);
}
