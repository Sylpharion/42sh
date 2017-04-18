/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:49:29 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 16:43:32 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char		*dup;
	size_t		size;
	int			i;
	int			j;

	dup = NULL;
	i = 0;
	j = 0;
	if (s)
	{
		size = ft_strlen(s);
		if ((dup = (char *)malloc(sizeof(char) * (size + 1))) == 0)
			return (NULL);
		while (s[i])
		{
			dup[j] = s[i];
			i++;
			j++;
		}
		dup[i] = '\0';
	}
	return (dup);
}
