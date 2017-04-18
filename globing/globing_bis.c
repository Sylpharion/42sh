/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:33:29 by ggobin            #+#    #+#             */
/*   Updated: 2017/01/25 15:25:20 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "globing.h"
#include "queries.h"
#include "is_matching.h"

static char	*el_new_from_to(char c, char *after, char *str, char *before)
{
	char *new;
	char *to_add;
	char *tmp;

	new = ft_strnew(1);
	to_add = ft_strnew(2);
	while (c <= str[3])
	{
		to_add[0] = c;
		tmp = ft_strnew(1);
		tmp = ft_strjoin_free(before, tmp, 2);
		tmp = ft_strjoin_free(tmp, to_add, 1);
		tmp = ft_strjoin_free(tmp, after, 1);
		new = ft_strjoin_free(new, tmp, 3);
		if (c < str[3])
			new = ft_strjoin_free(new, " ", 1);
		c++;
	}
	free(to_add);
	return (new);
}

char		*from_to(char *before, char *str)
{
	char		c;
	char		*after;
	char		*new;

	after = ft_strdup(ft_strchr(str, ']') + 1);
	if (str[1] > str[3])
	{
		c = str[1];
		str[1] = str[3];
		str[3] = c;
	}
	c = str[1];
	new = el_new_from_to(c, after, str, before);
	free(after);
	return (new);
}

static char	*generate_combos_bis(char *str)
{
	char *before;
	char *start;

	if (!(start = ft_strchr(str, '[')))
		return (str);
	before = ft_strsub(str, 0, start - str);
	if (start[2] == '-')
		str = from_to(before, start);
	else
		str = all(before, start);
	free(before);
	return (str);
}

char		*generate_combos(char *str)
{
	char		**double_tap;
	size_t		i;

	str = generate_combos_bis(str);
	double_tap = NULL;
	if (ft_strchr(str, '['))
	{
		double_tap = ft_strsplit(str, ' ');
		free(str);
		str = ft_strnew(1);
		i = 0;
		while (double_tap[i])
		{
			str = ft_strjoin_free(str, generate_combos(double_tap[i]), 3);
			if (double_tap[i + 1] != NULL)
				str = ft_strjoin_free(str, " ", 1);
			i++;
		}
	}
	ft_free_tab(&double_tap);
	return (str);
}
