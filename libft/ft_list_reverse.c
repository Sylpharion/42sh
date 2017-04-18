/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 11:37:45 by afougere          #+#    #+#             */
/*   Updated: 2016/04/24 15:53:02 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_reverse(t_list **begin_list)
{
	int		i;
	int		p;
	t_list	*tmp;

	i = 1;
	p = ft_list_size(*begin_list);
	tmp = *begin_list;
	while (i < p && *begin_list != NULL)
	{
		while ((*begin_list)->next != NULL && i < p)
		{
			ft_list_swap(*begin_list, (*begin_list)->next);
			*begin_list = (*begin_list)->next;
			i++;
		}
		i = 1;
		*begin_list = tmp;
		p--;
	}
}
