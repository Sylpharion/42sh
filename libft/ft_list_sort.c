/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 11:43:54 by afougere          #+#    #+#             */
/*   Updated: 2016/05/04 13:20:33 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*tmp;

	tmp = *begin_list;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
		{
			if (cmp(tmp->content, tmp->next->content) > 0)
			{
				ft_list_swap(tmp, tmp->next);
				tmp = *begin_list;
			}
			else
				tmp = tmp->next;
		}
	}
}
