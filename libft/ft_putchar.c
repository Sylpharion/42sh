/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:41:13 by afougere          #+#    #+#             */
/*   Updated: 2017/01/31 13:15:52 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_putchar(char c)
{
	int	fd;

	fd = open("/dev/tty", O_NOCTTY | O_WRONLY);
	write(fd, &c, 1);
}
