/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:50:28 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 19:22:39 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*copy;
	int		i;
	int		j;
	int		cpt;

	cpt = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	if ((copy = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	while (s1[j])
	{
		copy[j] = s1[j];
		j++;
	}
	while (s2[cpt])
	{
		copy[j] = s2[cpt];
		cpt++;
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
