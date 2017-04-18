/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:51:04 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 17:34:35 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		s_bis[i] = (*f)(i, s[i]);
		i++;
	}
	s_bis[i] = '\0';
	return (s_bis);
}
