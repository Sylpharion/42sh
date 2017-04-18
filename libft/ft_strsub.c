/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:54:20 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 18:57:53 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s_bis;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if ((s_bis = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (len > 0)
	{
		s_bis[i] = s[start];
		i++;
		start++;
		len--;
	}
	s_bis[i] = '\0';
	return (s_bis);
}
