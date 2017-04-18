/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:42:13 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 14:47:22 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	i;
	char			n_bis;

	i = 1;
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	while (n / i > 9)
		i *= 10;
	while (i > 0)
	{
		n_bis = (n / i) % 10 + '0';
		write(fd, &n_bis, 1);
		i /= 10;
	}
}
