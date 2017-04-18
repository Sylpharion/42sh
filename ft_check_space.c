/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 12:27:41 by afougere          #+#    #+#             */
/*   Updated: 2017/02/05 08:28:37 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		insert(t_list **lst, char elem, t_termio *termio)
{
	t_list	*new;

	new = ft_lstnew(&elem, 1);
	if (*lst && (*lst)->next == NULL && termio->i <= termio->prompt_len + 1)
	{
		new->prev = *lst;
		(*lst)->next = new;
		(*lst) = (*lst)->next;
	}
	else if (*lst == NULL || (*lst)->prev == NULL)
	{
		ft_lstadd(lst, new);
	}
	else
	{
		new->next = *lst;
		new->prev = (*lst)->prev;
		(*lst)->prev->next = new;
		(*lst)->prev = new;
		(*lst) = (*lst)->prev;
	}
}

static void	ft_check_space_before(t_list **lst, t_save *save, t_termio *termio)
{
	(void)save;
	while (*lst && (*lst)->next)
	{
		if (((*(char*)(*lst)->content == '|' &&
		*(char*)(*lst)->next->content == '|')
		|| (*(char*)(*lst)->content == '&' &&
		*(char*)(*lst)->next->content == '&')
		|| (*(char*)(*lst)->content == '>' &&
		*(char*)(*lst)->next->content == '>')
		|| (*(char*)(*lst)->content == '<' &&
		*(char*)(*lst)->next->content == '<')) &&
		(*lst)->next->next && *(char *)(*lst)->next->next->content != ' ')
			insert(&((*lst)->next->next), ' ', termio);
		*lst = (*lst)->next;
	}
}

void		ft_check_space_after(t_list **lst, t_save *save, t_termio *termio)
{
	t_list *tmp;

	tmp = *lst;
	if (tmp && tmp->next)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	while (tmp && tmp->prev)
	{
		if (((*(char*)tmp->content == '|' &&
		*(char*)tmp->prev->content == '|')
		|| (*(char*)tmp->content == '&' &&
		*(char*)tmp->prev->content == '&')
		|| (*(char*)tmp->content == '<' &&
		*(char*)tmp->prev->content == '<')
		|| (*(char*)tmp->content == '>' &&
		*(char*)tmp->prev->content == '>')) &&
		tmp->prev->prev && *(char *)tmp->prev->prev->content != ' ')
			insert(&(tmp->prev), ' ', termio);
		tmp = tmp->prev;
	}
	ft_check_space_before(&tmp, save, termio);
}
