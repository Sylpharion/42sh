/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_term.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 12:50:16 by afougere          #+#    #+#             */
/*   Updated: 2017/01/25 15:21:35 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		ft_all_list_to_str(t_termio *termio)
{
	int		size;
	t_list	*list;

	termio->save_cut = NULL;
	list = termio->history->content;
	if (list && list->prev)
	{
		while (list->prev)
			list = list->prev;
	}
	size = ft_list_size(list);
	termio->save_cut = ft_memalloc(size + 1);
	size--;
	while (list && size >= 0)
	{
		termio->save_cut[size] = *((char *)list->content);
		remove_elem(&list);
		size--;
	}
	termio->history->content = list;
}

static void	ft_refill_lst(t_termio *termio, t_save *save, char *str)
{
	size_t		i;
	t_list		*list;

	i = 0;
	list = termio->history->content;
	while (i < ft_strlen(str))
	{
		insert_elem(&list, str[i], save, termio);
		i++;
	}
	termio->history->content = list;
}

void		ft_part_list_to_str(t_termio *termio, int i, t_save *save)
{
	t_list	*lst;
	char	*tmp;
	int		size;
	char	*tmpbis;

	lst = termio->history->content;
	while (lst && lst->next)
		lst = lst->next;
	size = ft_list_size_by_prev(lst);
	tmp = ft_memalloc(size + 1);
	while (lst)
	{
		tmp[i] = *((char *)lst->content);
		i++;
		lst = lst->prev;
	}
	tmpbis = &tmp[termio->i - termio->prompt_len];
	termio->save_cut = ft_strdup(tmpbis);
	tmpbis[0] = 0;
	ft_lst_free(((t_list **)(&termio->history->content)));
	ft_refill_lst(termio, save, tmp);
	free(tmp);
}

void		ft_save_line_to_lst(t_termio *termio, t_save *save)
{
	size_t		i;
	t_list		*list;

	i = 0;
	list = termio->history->content;
	while (i < ft_strlen(termio->save_cut))
	{
		termio->size++;
		termio->i++;
		if (insert_elem(&list, termio->save_cut[i], save, termio))
			ft_putchar(termio->save_cut[i]);
		i++;
	}
	termio->history->content = list;
}

void		ft_save_history(t_termio *termio, t_save *save, char buffer[1024])
{
	t_list *lst;

	lst = NULL;
	if (buffer[2] == 65 || buffer[2] == 66)
	{
		ft_history(termio, save, buffer[2], lst);
		if (termio->history)
		{
			ft_lst_free(&termio->cp);
			termio->cp =
		ft_cp_env_to_sv(((t_list **)(&termio->history->content)));
		}
	}
}
