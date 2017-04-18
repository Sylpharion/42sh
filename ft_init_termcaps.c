/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_termcaps.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 15:09:51 by afougere          #+#    #+#             */
/*   Updated: 2016/12/01 15:24:45 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_term(t_save *save, t_termio *termio)
{
	struct termios	term;
	struct termios	term_bis;
	int				i;

	i = 1;
	if (tgetent(0, getenv("TERM")) == -1)
		tgetent(0, "xterm-256color");
	if (tcgetattr(0, &term) == -1)
		return (-1);
	if (tcgetattr(0, &term_bis) == -1)
		return (-1);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	i = ft_puts_goto(termio, save);
	if (tcsetattr(0, TCSANOW, &term_bis) == -1)
		return (-1);
	return (i);
}

void	ft_init_var_save(t_save **save)
{
	(*save)->utils->j = 0;
	(*save)->utils->info_col->long_word = 0;
	(*save)->utils->nb_words = 0;
	(*save)->utils->aff_or_not = 1;
}
