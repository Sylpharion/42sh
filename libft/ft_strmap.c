/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:50:55 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 17:33:55 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*s_bis;

	i = 0;
	if (s == NULL)
		return (NULL);
	s_bis = ft_strnew(ft_strlen(s));
	if (s_bis == NULL)
		return (NULL);
	while (s[i])
	{
		s_bis[i] = (*f)(s[i]);
		i++;
	}
	s_bis[i] = '\0';
	return (s_bis);
}
