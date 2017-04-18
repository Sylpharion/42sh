/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:42:26 by afougere          #+#    #+#             */
/*   Updated: 2017/01/31 13:17:41 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

void	ft_putstr(char const *s)
{
	int		n;
	int		fd;

	fd = open("/dev/tty", O_NOCTTY | O_WRONLY);
	n = ft_strlen(s);
	write(fd, s, n);
	close(fd);
}
