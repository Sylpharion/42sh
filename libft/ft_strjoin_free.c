/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:19:41 by afougere          #+#    #+#             */
/*   Updated: 2016/11/29 10:44:59 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	free_if(int nb, char **s1, char **s2)
{
	if (nb == 1 || nb == 3)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (nb == 2 || nb == 3)
	{
		free(*s2);
		*s2 = NULL;
	}
}

char	*ft_strjoin_free(char *s1, char *s2, int nb)
{
	char	*copy;
	int		i;
	int		j;
	int		cpt;

	cpt = 0;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	if ((copy = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	while (s1[++j])
		copy[j] = s1[j];
	while (s2[cpt])
		copy[j++] = s2[cpt++];
	free_if(nb, &s1, &s2);
	copy[j] = '\0';
	return (copy);
}
