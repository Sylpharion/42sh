/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:12:18 by afougere          #+#    #+#             */
/*   Updated: 2016/03/14 17:17:47 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_sqrt(double nb)
{
	double res;
	double sv;

	res = 1;
	sv = 0;
	if (nb <= 0)
		return (0);
	while (sv != res)
	{
		sv = res;
		res = 0.5 * (res + nb / res);
	}
	return (res);
}
