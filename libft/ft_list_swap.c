/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 15:48:05 by afougere          #+#    #+#             */
/*   Updated: 2016/04/24 15:52:43 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_swap(t_list *list, t_list *list_bis)
{
	void *content;

	content = list->content;
	list->content = list_bis->content;
	list_bis->content = content;
}
