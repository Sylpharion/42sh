/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:53:18 by afougere          #+#    #+#             */
/*   Updated: 2016/05/12 14:35:19 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int		get_next_line(const int fd, char **line)
{
	static char *end_read;
	char		*sv;
	size_t		i;
	t_gnl		gnl;

	gnl.fd = fd;
	sv = NULL;
	gnl.buf = (char *)malloc(sizeof(char) * (BUF_SIZE + 1));
	while ((end_read == NULL || ft_strchr(end_read, '\n') == NULL) &&
			(sv == NULL || ft_strchr(sv, '\n') == NULL))
		if ((i = ft_fill_str(gnl, line, &sv, &end_read)) != 3)
			return (i);
	if ((end_read != NULL && ft_strlen(end_read) != 0 && sv != NULL) &&
			(sv = ft_strjoin_free(end_read, sv, 1)) == NULL)
		return (-1);
	else if (sv == NULL)
		sv = ft_strdup(end_read);
	i = ft_strchr(sv, '\n') - sv;
	if ((*line = ft_strsub(sv, 0, i)) == NULL)
		return (ft_free(&sv));
	if ((end_read = ft_strsub(sv, i + 1, ft_strlen(i + sv + 1))) == NULL)
		return (ft_free(&sv));
	free(sv);
	free(gnl.buf);
	return (ft_strlen(end_read) == 0 ? ft_free(&end_read) * -1 : 1);
}

int		ft_fill_str(t_gnl gnl, char **line, char **sv, char **end_read)
{
	int car;

	if ((car = read(gnl.fd, gnl.buf, BUF_SIZE)) <= 0)
	{
		if (car < 0)
			return (-1);
		return (ft_fill_str_bis(gnl, line, sv, end_read));
	}
	gnl.buf[car] = '\0';
	if (*sv == NULL)
	{
		if ((*sv = ft_strdup(gnl.buf)) == NULL)
			return (-1);
	}
	else if ((*sv = ft_strjoin_free(*sv, gnl.buf, 1)) == NULL)
		return (-1);
	return (3);
}

int		ft_fill_str_bis(t_gnl gnl, char **line, char **sv, char **end_read)
{
	if (*end_read == NULL || ft_strlen(*end_read) == 0)
	{
		if (*sv == NULL)
		{
			free(gnl.buf);
			return (0);
		}
		if ((*line = ft_strdup(*sv)) == NULL)
			return (ft_free(sv));
	}
	else
	{
		if (*sv == NULL)
		{
			*line = ft_strdup(*end_read);
			free(*end_read);
			*end_read = NULL;
		}
		else
			*line = ft_strjoin_free(*sv, *end_read, 3);
		*end_read = NULL;
		return (1);
	}
	free(gnl.buf);
	return (1);
}

int		ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (-1);
}
