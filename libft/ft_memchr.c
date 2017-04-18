/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:39:31 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 14:39:32 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	int i;

	i = 0;
	while (n > 1 && ((unsigned char *)s)[i] != (unsigned char)c)
	{
		i++;
		n--;
	}
	if (n == 1 && ((unsigned char *)s)[i] != (unsigned char)c)
		return (NULL);
	return ((void *)((unsigned char *)s + i));
}
