/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 11:37:10 by afougere          #+#    #+#             */
/*   Updated: 2017/01/25 15:12:12 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		ft_dl_line(t_list **list, t_save *save, t_termio *termio)
{
	termio->i--;
	termio->size--;
	remove_elem(list);
	ft_clear_cmd_backspace(termio);
	ft_replace_curser_and_aff(*list, save, termio);
}

static void	ft_multi_line_up(t_termio *termio, struct winsize ws, t_list **lst)
{
	int nb;
	int sv;

	nb = termio->i / ws.ws_col;
	sv = termio->i;
	tputs(tgetstr("up", NULL), 1, outc);
	termio->i -= ws.ws_col;
	while (termio->i < termio->prompt_len)
	{
		tputs(tgetstr("nd", NULL), 1, outc);
		termio->i++;
	}
	while (sv > termio->i && (*lst)->next)
	{
		*lst = (*lst)->next;
		sv--;
	}
	termio->uppped = 1;
}

static void	ft_part_multi_line_down(t_termio *termio, struct winsize ws)
{
	int nb;

	nb = 0;
	tputs(tgetstr("do", NULL), 1, outc);
	if (termio->i / ws.ws_col == termio->size / ws.ws_col - 1 &&
	termio->i % ws.ws_col > termio->size % ws.ws_col)
	{
		while (nb < termio->size % ws.ws_col)
		{
			tputs(tgetstr("nd", NULL), 1, outc);
			nb++;
		}
		termio->i = termio->size;
	}
	else
	{
		while (nb < termio->i % ws.ws_col)
		{
			tputs(tgetstr("nd", NULL), 1, outc);
			nb++;
		}
		termio->i += ws.ws_col;
	}
}

void		ft_multi_line(t_termio *termio, int buf, struct winsize ws)
{
	int		sv;
	t_list	*lst;

	lst = termio->history->content;
	if (buf == 53 && termio->i / (float)ws.ws_col >= 1.0f)
		ft_multi_line_up(termio, ws, &lst);
	else if (buf == 54 && termio->i / ws.ws_col < termio->size / ws.ws_col)
	{
		sv = termio->i;
		ft_part_multi_line_down(termio, ws);
		while (sv < termio->i && lst->prev)
		{
			lst = lst->prev;
			sv++;
		}
	}
	termio->history->content = lst;
}

void		ft_left_right(t_termio *termio, int buf, struct winsize ws)
{
	if (buf == 68 && termio->i > termio->prompt_len && termio->history->content)
	{
		termio->uppped = 0;
		termio->i--;
		if (((t_list *)termio->history->content)->next)
			termio->history->content =
			((t_list *)termio->history->content)->next;
		tputs(tgetstr("le", NULL), 1, outc);
	}
	else if (buf == 67 && termio->i < termio->size)
	{
		termio->uppped = 0;
		if (((t_list *)termio->history->content)->prev &&
			termio->i > termio->prompt_len)
			termio->history->content =
			((t_list *)termio->history->content)->prev;
		termio->i++;
		if (termio->i % ws.ws_col == 0)
			tputs(tgetstr("do", NULL), 1, outc);
		else
			tputs(tgetstr("nd", NULL), 1, outc);
	}
}
