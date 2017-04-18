/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:51:55 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 16:46:17 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	ma_taille;
	size_t	i;

	i = 0;
	ma_taille = ft_strlen(src);
	while (i < n)
	{
		dest[i] = src[i];
		if (n > ma_taille)
			if (i >= ma_taille)
				dest[i] = '\0';
		++i;
	}
	return (dest);
}
