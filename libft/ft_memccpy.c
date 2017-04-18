/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:39:22 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 18:54:14 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*dest_bis;
	unsigned char	*src_bis;
	unsigned char	c_bis;
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	dest_bis = (unsigned char *)dest;
	src_bis = (unsigned char *)src;
	c_bis = (unsigned char)c;
	while (i < n)
	{
		dest_bis[i] = src_bis[j];
		if (dest_bis[i] == c_bis)
			return (&dest_bis[i + 1]);
		j++;
		i++;
	}
	return (NULL);
}
