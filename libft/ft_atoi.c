/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:37:03 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 14:58:36 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *nptr)
{
	int i;
	int signe;

	signe = 1;
	i = 0;
	while ((*nptr <= '\r' && *nptr >= '\t') || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
	{
		signe = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr <= '9' && *nptr >= '0')
	{
		i = (i * 10) + *nptr - '0';
		nptr++;
	}
	return (i * signe);
}
