/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_by_word_right.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 11:50:13 by afougere          #+#    #+#             */
/*   Updated: 2017/01/25 15:24:13 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	ft_replace_curser_right(struct winsize ws, t_termio *termio,
				int *nb)
{
	if (*nb > 1)
	{
		while (*nb > 0)
		{
			(*nb)--;
			if (termio->i % ws.ws_col == ws.ws_col - 1)
				tputs(tgetstr("do", NULL), 1, outc);
			else
				tputs(tgetstr("nd", NULL), 1, outc);
			termio->i++;
		}
	}
}

static void	ft_word_right_space(t_list **sv, t_termio *termio,
				struct winsize ws, int nb)
{
	t_list	*sv_bis;
	int		nb_bis;

	sv_bis = *sv;
	nb_bis = nb;
	*sv = (*sv)->prev;
	while (*sv && (*sv)->prev && *(char *)(*sv)->content == ' ')
	{
		nb++;
		*sv = (*sv)->prev;
	}
	if (*(char *)(*sv)->content == ' ' && (*sv)->prev == NULL)
	{
		nb = nb_bis;
		*sv = sv_bis;
	}
	while (*sv && (*sv)->prev && *(char *)(*sv)->prev->content != ' ')
	{
		nb++;
		*sv = (*sv)->prev;
	}
	if (termio->i == termio->prompt_len)
		nb++;
	ft_replace_curser_right(ws, termio, &nb);
}

static void	ft_replace_curser_right_first(struct winsize ws,
				t_termio *termio, int *nb)
{
	if (termio->i == termio->prompt_len)
		(*nb)++;
	while (*nb > 0)
	{
		(*nb)--;
		if (termio->i % ws.ws_col == ws.ws_col - 1)
			tputs(tgetstr("do", NULL), 1, outc);
		else
			tputs(tgetstr("nd", NULL), 1, outc);
		termio->i++;
	}
}

void		ft_word_right(t_termio *termio)
{
	t_list			*sv;
	int				nb;
	struct winsize	ws;

	nb = 0;
	ioctl(0, TIOCGWINSZ, &ws);
	sv = termio->history->content;
	if (sv->prev)
	{
		if (*(char *)sv->prev->content != ' ')
		{
			while (sv && sv->prev && *(char *)sv->prev->content != ' ')
			{
				sv = sv->prev;
				nb++;
			}
			ft_replace_curser_right_first(ws, termio, &nb);
		}
		else if (*(char *)sv->prev->content == ' ')
			ft_word_right_space(&sv, termio, ws, 1);
	}
	termio->history->content = sv;
}
