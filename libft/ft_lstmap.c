/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:38:56 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 14:59:47 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *tmp;

	if ((new = (*f)(lst)) == NULL)
		return (NULL);
	tmp = new;
	while (lst && lst->next)
	{
		new->next = (*f)(lst->next);
		lst = lst->next;
		new = new->next;
	}
	return (tmp);
}
