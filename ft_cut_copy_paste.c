/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_copy_paste.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 12:50:11 by afougere          #+#    #+#             */
/*   Updated: 2017/01/25 15:01:24 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <stdio.h>

static void	ft_cut_after(t_save *save, t_termio *termio)
{
	if (termio->save_cut)
		free(termio->save_cut);
	ft_part_list_to_str(termio, 0, save);
	ft_clear_cmd(termio);
	ft_lst_to_str(termio->history->content, save, termio);
	ft_clear_cmd_backspace(termio);
	ft_putstr(save->line);
	termio->i = ft_strlen(save->line) + termio->prompt_len;
	termio->size = termio->i;
}

static void	ft_cut_all(t_termio *termio, t_save *save)
{
	if (termio->save_cut)
		free(termio->save_cut);
	ft_all_list_to_str(termio);
	ft_lst_to_str(termio->history->content, save, termio);
	ft_clear_cmd_backspace(termio);
	termio->i = termio->prompt_len;
	termio->size = termio->i;
}

void		ft_cut_copy_paste(t_save *save, t_termio *termio, char buf)
{
	if (buf == 21 && termio->history->content)
		ft_cut_all(termio, save);
	else if (buf == 11 && termio->history->content)
		ft_cut_after(save, termio);
	else if (buf == 16 && termio->save_cut)
		ft_save_line_to_lst(termio, save);
}
