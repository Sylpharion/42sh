/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff_term.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 11:20:34 by afougere          #+#    #+#             */
/*   Updated: 2017/02/01 15:05:46 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		ft_aff(t_list *lst, t_save *save, t_termio *termio)
{
	ft_clear_cmd(termio);
	ft_replace_curser_and_aff(lst, save, termio);
}

void		ft_replace_curser_prompt(t_termio *termio)
{
	int	j;

	j = 0;
	tputs(tgetstr("cr", NULL), 1, outc);
	while (j < termio->prompt_len)
	{
		tputs(tgetstr("nd", NULL), 1, outc);
		j++;
	}
	tputs(tgetstr("ce", NULL), 1, outc);
}

static void	ft_init_clear_cmd(t_termio *termio)
{
	struct winsize		ws;
	int					taille;

	taille = 0;
	ioctl(0, TIOCGWINSZ, &ws);
	termio->nb_lines = termio->size / ws.ws_col;
	termio->cur_line = termio->i / ws.ws_col;
	if (termio->uppped == 1 && (termio->i - 1) % ws.ws_col == 0)
		taille = 1;
	if (termio->i % ws.ws_col == 0)
		termio->cur_line--;
	tputs(tgetstr("cr", NULL), 1, outc);
	while (termio->cur_line > 0)
	{
		tputs(tgetstr("up", NULL), 1, outc);
		termio->cur_line--;
	}
	ft_replace_curser_prompt(termio);
}

void		ft_clear_cmd(t_termio *termio)
{
	int					old_i;

	old_i = 0;
	ft_init_clear_cmd(termio);
	if (termio->nb_lines > 0)
	{
		tputs(tgetstr("do", NULL), 1, outc);
		tputs(tgetstr("cr", NULL), 1, outc);
		while (old_i < termio->nb_lines - 1)
		{
			tputs(tgetstr("ce", NULL), 1, outc);
			tputs(tgetstr("do", NULL), 1, outc);
			old_i++;
		}
		old_i = 0;
		while (old_i < termio->nb_lines)
		{
			tputs(tgetstr("up", NULL), 1, outc);
			old_i++;
		}
		ft_replace_curser_prompt(termio);
	}
}

void		ft_replace_curser_and_aff(t_list *lst, t_save *save,
				t_termio *termio)
{
	int					l;
	struct winsize		ws;

	ioctl(0, TIOCGWINSZ, &ws);
	ft_lst_to_str(lst, save, termio);
	ft_putstr(save->line);
	l = termio->size;
	termio->nb_lines = termio->size / ws.ws_col;
	termio->cur_line = termio->i / ws.ws_col;
	if ((ws.ws_col * termio->nb_lines) - termio->i == termio->size - termio->i)
		l--;
	while (l > termio->i)
	{
		tputs(tgetstr("le", NULL), 1, outc);
		l--;
	}
	if (termio->i == termio->prompt_len)
	{
		free(save->line);
		save->line = NULL;
	}
}
