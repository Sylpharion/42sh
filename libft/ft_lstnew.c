/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:39:05 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 14:39:06 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_maillon;

	if (((new_maillon = ft_memalloc(sizeof(t_list)))) == NULL)
		return (NULL);
	if (content == NULL || content_size == 0)
	{
		new_maillon->content = NULL;
		new_maillon->content_size = 0;
	}
	else
	{
		if ((new_maillon->content = ft_memalloc(content_size)) == NULL)
			return (NULL);
		ft_memcpy(new_maillon->content, content, content_size);
		new_maillon->content_size = content_size;
	}
	new_maillon->next = NULL;
	new_maillon->prev = NULL;
	return (new_maillon);
}
