/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 11:40:05 by afougere          #+#    #+#             */
/*   Updated: 2016/05/23 14:11:14 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_remove_if(t_list **begin_list, void *content_ref, int (*cmp)())
{
	t_list *tmp;
	t_list *tmp_bis;

	while (*begin_list != NULL && cmp((*begin_list)->content, content_ref) == 0)
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(tmp->content);
		free(tmp);
	}
	tmp_bis = *begin_list;
	while (tmp_bis != NULL && tmp_bis->next != NULL)
	{
		tmp = tmp_bis->next;
		if (cmp(tmp->content, content_ref) == 0)
		{
			tmp_bis->next = tmp->next;
			free(tmp->content);
			free(tmp);
		}
		tmp_bis = tmp_bis->next;
	}
}
