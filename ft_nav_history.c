/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nav_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 11:48:10 by afougere          #+#    #+#             */
/*   Updated: 2017/01/25 15:08:58 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	ft_history_bis(t_termio *termio, t_list *lst, t_save *save)
{
	int j;

	termio->history = termio->history->prev;
	lst = ((t_list *)termio->history->content);
	while (lst && lst->prev)
		lst = lst->prev;
	j = termio->i;
	ft_clear_cmd_backspace(termio);
	ft_lst_to_str(lst, save, termio);
	ft_putstr(save->line);
	termio->size = ft_list_size(lst) + termio->prompt_len;
	termio->i = termio->size;
	while (j < termio->size && termio->history->content &&
	((t_list *)termio->history->content)->prev)
	{
		termio->history->content =
		((t_list *)termio->history->content)->prev;
		j++;
	}
}

void		ft_history(t_termio *termio, t_save *save, char buf, t_list *lst)
{
	int j;

	if (buf == 65 && termio->history && termio->history->next)
	{
		termio->history = termio->history->next;
		lst = ((t_list *)termio->history->content);
		while (lst && lst->prev)
			lst = lst->prev;
		j = termio->i;
		ft_clear_cmd_backspace(termio);
		ft_lst_to_str(lst, save, termio);
		ft_putstr(save->line);
		termio->size = ft_list_size(lst) + termio->prompt_len;
		termio->i = termio->size;
		while (j < termio->size && termio->history->content &&
		((t_list *)termio->history->content)->prev)
		{
			termio->history->content =
			((t_list *)termio->history->content)->prev;
			j++;
		}
	}
	else if (buf == 66 && termio->history && termio->history->prev)
		ft_history_bis(termio, lst, save);
}
