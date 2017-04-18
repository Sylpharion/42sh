/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_backspace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 10:56:19 by afougere          #+#    #+#             */
/*   Updated: 2017/02/01 14:55:53 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	ft_init_clear_cmd_backspace(t_termio *termio)
{
	struct winsize		ws;

	ioctl(0, TIOCGWINSZ, &ws);
	termio->nb_lines = termio->size / ws.ws_col;
	termio->cur_line = termio->i / ws.ws_col;
	if (termio->i < termio->size)
		if (termio->i - ws.ws_col * termio->cur_line + 1 == ws.ws_col)
			termio->cur_line++;
	tputs(tgetstr("cr", NULL), 1, outc);
	while (termio->cur_line > 0)
	{
		tputs(tgetstr("up", NULL), 1, outc);
		termio->cur_line--;
	}
	ft_replace_curser_prompt(termio);
}

void		ft_clear_cmd_backspace(t_termio *termio)
{
	int old_i;

	old_i = 0;
	ft_init_clear_cmd_backspace(termio);
	if (termio->nb_lines > 0)
	{
		tputs(tgetstr("do", NULL), 1, outc);
		tputs(tgetstr("cr", NULL), 1, outc);
		while (old_i < termio->nb_lines)
		{
			tputs(tgetstr("ce", NULL), 1, outc);
			tputs(tgetstr("do", NULL), 1, outc);
			old_i++;
		}
		old_i = 0;
		while (old_i < termio->nb_lines + 1)
		{
			tputs(tgetstr("up", NULL), 1, outc);
			old_i++;
		}
		ft_replace_curser_prompt(termio);
	}
}

void		ft_aff_backspace(t_list *lst, t_save *save, t_termio *termio)
{
	struct winsize		ws;

	ioctl(0, TIOCGWINSZ, &ws);
	ft_clear_cmd_backspace(termio);
	ft_replace_curser_and_aff(lst, save, termio);
}
