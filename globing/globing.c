/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:32:54 by ggobin            #+#    #+#             */
/*   Updated: 2017/01/25 15:26:51 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "globing.h"
#include "queries.h"
#include "is_matching.h"

char		*all(char *before, char *str)
{
	t_all		a;

	a.after = ft_strdup(ft_strchr(str, ']') + 1);
	a.to_add = ft_strnew(2);
	a.end = ft_strchr(str, ']');
	a.new = ft_strnew(1);
	*a.end = 0;
	a.all_chars = ft_strdup(&str[1]);
	a.i = -1;
	while (a.all_chars[++a.i])
	{
		a.to_add[0] = a.all_chars[a.i];
		a.tmp = ft_strnew(1);
		a.tmp = ft_strjoin_free(before, a.tmp, 2);
		a.tmp = ft_strjoin_free(a.tmp, a.to_add, 1);
		a.tmp = ft_strjoin_free(a.tmp, a.after, 1);
		a.new = ft_strjoin_free(a.new, a.tmp, 3);
		if (a.all_chars[a.i + 1])
			a.new = ft_strjoin_free(a.new, " ", 1);
	}
	*a.end = ']';
	free(a.all_chars);
	free(a.to_add);
	free(a.after);
	return (a.new);
}

int			check_pattern(char *pattern)
{
	int			open;
	int			close;
	size_t		i;

	i = 0;
	open = 0;
	close = 0;
	while (pattern[i])
	{
		if (pattern[i] == '[' && close == open)
			open++;
		else if (pattern[i] == '[' && close != open)
			return (1);
		if (pattern[i] == ']')
			close++;
		i++;
	}
	if (open != close)
		return (1);
	return (0);
}

static int	ft_glob_bis(char **s_fmt, char *name, char **queries, int i)
{
	if (ft_strchr(s_fmt[i], '?'))
		queries = init_queries(s_fmt, i);
	if (is_matching_star(name, s_fmt[i]))
	{
		if (queries)
		{
			delete_queries(&queries);
			if (is_matching_query(name, s_fmt[i]))
			{
				ft_free_tab(&s_fmt);
				return (1);
			}
			else
			{
				ft_free_tab(&s_fmt);
				return (0);
			}
		}
		ft_free_tab(&s_fmt);
		return (1);
	}
	if (queries)
		delete_queries(&queries);
	return (2);
}

static int	ft_query(char **s_fmt, char *name, int i)
{
	if (ft_strchr(s_fmt[i], '?'))
	{
		if (is_matching_query(name, s_fmt[i]))
		{
			ft_free_tab(&s_fmt);
			return (1);
		}
	}
	if (!ft_strcmp(s_fmt[i], name))
	{
		ft_free_tab(&s_fmt);
		return (1);
	}
	return (0);
}

int			ft_glob(t_glob g, char *name)
{
	char		**s_fmt;
	size_t		i;
	char		**queries;
	int			ret;

	queries = NULL;
	s_fmt = NULL;
	if (!g.fmt)
		return (0);
	s_fmt = ft_strsplit(g.fmt, ' ');
	i = 0;
	while (s_fmt[i])
	{
		if (ft_strchr(s_fmt[i], '*'))
			if ((ret = ft_glob_bis(s_fmt, name, queries, i)) != 2)
				return (ret);
		if (ft_query(s_fmt, name, i))
			return (1);
		i++;
	}
	ft_free_tab(&s_fmt);
	return (0);
}
