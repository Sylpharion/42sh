/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:40:21 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 19:24:28 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int					i;
	unsigned char		*dest_bis;

	i = 0;
	dest_bis = (unsigned char *)dest;
	if (dest_bis > (unsigned char *)src)
		ft_memcpy(dest_bis, src, n);
	else
	{
		while (n > 0)
		{
			dest_bis[i] = ((unsigned char *)src)[i];
			i++;
			n--;
		}
	}
	return (dest);
}
