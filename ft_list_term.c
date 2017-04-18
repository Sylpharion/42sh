/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 11:27:56 by afougere          #+#    #+#             */
/*   Updated: 2017/02/05 16:03:08 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			insert_elem(t_list **lst, char elem, t_save *save, t_termio *termio)
{
	t_list	*new;

	new = ft_lstnew(&elem, 1);
	if (*lst && (*lst)->next == NULL && termio->i <= termio->prompt_len + 1)
	{
		new->prev = *lst;
		(*lst)->next = new;
		(*lst) = (*lst)->next;
		ft_aff(*lst, save, termio);
	}
	else if (*lst == NULL || (*lst)->prev == NULL)
	{
		ft_lstadd(lst, new);
		return (1);
	}
	else
	{
		new->next = *lst;
		new->prev = (*lst)->prev;
		(*lst)->prev->next = new;
		(*lst)->prev = new;
		(*lst) = (*lst)->prev;
		ft_aff(*lst, save, termio);
	}
	return (0);
}

void		remove_elem(t_list **lst)
{
	t_list	*tmp;

	if ((*lst)->prev == NULL)
	{
		tmp = (*lst);
		(*lst) = (*lst)->next;
		if (*lst)
			(*lst)->prev = NULL;
		free(tmp->content);
		free(tmp);
	}
	else
	{
		tmp = *lst;
		(*lst)->prev->next = (*lst)->next;
		if ((*lst)->next)
		{
			(*lst)->next->prev = (*lst)->prev;
			*lst = tmp->next;
		}
		else
			*lst = tmp->prev;
		free(tmp->content);
		free(tmp);
	}
}

static void	ft_save_history_glob(t_save *save, t_termio *termio)
{
	int i;

	i = 0;
	termio->history_save = NULL;
	if (save->utils->aff_or_not == 0)
	{
		ft_lstadd(&termio->history_save, ft_lstnew(NULL, 0));
		while (save->line[i])
		{
			insert_elem((t_list **)(&termio->history_save->content),
			save->line[i], save, termio);
			i++;
		}
	}
}

void		ft_str_to_lst(t_list **lst, char *content, t_save *save,
				t_termio *termio)
{
	int		i;
	t_list	*tmp;

	i = 0;
	ft_save_history_glob(save, termio);
	while (content[i])
	{
		insert_elem(lst, content[i], save, termio);
		termio->size++;
		i++;
	}
	termio->size -= ft_strlen(save->utils->save);
	termio->i = termio->size;
	if (save->utils->aff_or_not == 1)
	{
		ft_clear_cmd(termio);
		tmp = *lst;
		while (tmp && tmp->next)
			tmp = tmp->next;
		while (tmp)
		{
			ft_putchar(*(char *)tmp->content);
			tmp = tmp->prev;
		}
	}
}
