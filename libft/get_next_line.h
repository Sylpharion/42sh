/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:53:36 by afougere          #+#    #+#             */
/*   Updated: 2016/05/15 10:19:12 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define BUF_SIZE 30

typedef struct		s_gnl
{
	int				fd;
	char			*buf;
}					t_gnl;

int					get_next_line(const int fd, char **line);
int					ft_fill_str(t_gnl gnl, char **line, char **sv,
					char **end_read);
int					ft_free(char **str);
int					ft_fill_str_bis(t_gnl gnl, char **line, char **sv,
					char **end_read);

#endif
