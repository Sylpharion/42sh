/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size_by_prev.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:05:02 by afougere          #+#    #+#             */
/*   Updated: 2016/10/08 13:24:53 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_list_size_by_prev(t_list *lst)
{
	int size;

	size = 0;
	while (lst)
	{
		lst = lst->prev;
		size++;
	}
	return (size);
}
