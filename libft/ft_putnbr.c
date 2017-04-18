/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:42:02 by afougere          #+#    #+#             */
/*   Updated: 2016/03/14 15:30:47 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr(int n)
{
	char			str;
	unsigned int	nb;

	str = '0';
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	nb = n;
	if (nb < 10)
	{
		str += nb;
		write(1, &str, 1);
	}
	else
	{
		n = nb / 10;
		ft_putnbr(n);
		ft_putnbr(nb % 10);
	}
}
