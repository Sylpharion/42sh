/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:53:49 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 15:02:44 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
		i++;
	while (i > 0 && s[i] != c)
		i--;
	if (i == 0 && s[i] != c)
		return (NULL);
	return ((char *)s + i);
}
