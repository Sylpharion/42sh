/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which_term.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 16:26:18 by afougere          #+#    #+#             */
/*   Updated: 2017/01/25 15:21:00 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "Auto_completion/auto.h"

static void	ft_which_term(t_termio *termio, t_save *save, char buffer[1024],
				struct winsize ws)
{
	if (buffer[2] == 53 || buffer[2] == 54)
		ft_multi_line(termio, buffer[2], ws);
	if (termio->history->content && buffer[0] == 127 &&
		(termio->i > termio->prompt_len))
		ft_dl_line(((t_list **)(&termio->history->content)), save, termio);
	if (buffer[0] == 27 && (buffer[2] == 72 || buffer[2] == 70))
		ft_home_end(((t_list **)(&termio->history->content)),
		termio, buffer[2]);
	if (buffer[2] == 68 || buffer[2] == 67)
		ft_left_right(termio, buffer[2], ws);
}

int			ft_puts_goto_bis(char buffer[1024], t_termio *termio, t_list *sv,
				t_save *save)
{
	struct winsize	ws;
	char			*cp;

	cp = NULL;
	ioctl(0, TIOCGWINSZ, &ws);
	if (buffer[0] == 9)
		ft_tab(save->utils, save);
	if (buffer[0] == 10)
	{
		ft_check_space_after((t_list **)(&termio->history->content), save,
		termio);
		ft_enter_and_glob(save, save->termio, cp);
		if (!ft_return(termio, sv))
			return (0);
	}
	ft_which_term(termio, save, buffer, ws);
	return (1);
}
