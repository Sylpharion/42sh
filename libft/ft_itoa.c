/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:37:50 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 14:38:02 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*chiffre(int n)
{
	char *str;

	if (n < 0)
	{
		if ((str = (char *)malloc(sizeof(char) * 3)) == NULL)
			return (NULL);
		str[0] = '-';
		str[1] = -n + '0';
		str[2] = '\0';
	}
	else
	{
		if ((str = (char *)malloc(sizeof(char) * 2)) == NULL)
			return (NULL);
		str[0] = n + '0';
		str[1] = '\0';
	}
	return (str);
}

static char	*number_bis(unsigned int nb, int i, int negatif)
{
	char	*str;

	if ((str = (char *)malloc(sizeof(char) * (i + 1 + negatif))) == NULL)
		return (NULL);
	str[i + negatif] = '\0';
	while (i > 0)
	{
		i--;
		str[i + negatif] = nb % 10 + '0';
		nb /= 10;
	}
	if (negatif == 1)
		str[i] = '-';
	return (str);
}

static char	*number(int n)
{
	int				negatif;
	unsigned int	nb;
	int				i;

	negatif = 0;
	i = 0;
	if (n < 0)
	{
		negatif = 1;
		n = -n;
	}
	nb = n;
	while (nb > 0)
	{
		i++;
		nb /= 10;
	}
	return (number_bis((unsigned int)n, i, negatif));
}

char		*ft_itoa(int n)
{
	if (n > -10 && n < 10)
		return (chiffre(n));
	else
		return (number(n));
}
