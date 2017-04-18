/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 13:25:42 by afougere          #+#    #+#             */
/*   Updated: 2016/11/30 09:33:48 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_free(t_list **lst)
{
	t_list *tmp;

	tmp = NULL;
	if (*lst && (*lst)->prev)
	{
		while ((*lst)->prev)
			*lst = (*lst)->prev;
	}
	if (*lst)
	{
		while (*lst)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			free(tmp->content);
			free(tmp);
		}
	}
	*lst = NULL;
}
