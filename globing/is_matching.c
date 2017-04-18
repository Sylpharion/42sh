/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_matching.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:41:46 by afougere          #+#    #+#             */
/*   Updated: 2016/11/08 11:42:00 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "is_matching.h"

static int		is_matching_star_bis(char *s2,
char *s1, int i)
{
	char	*cur;
	char	**s_s2;

	cur = s1;
	s_s2 = ft_strsplit(s2, '*');
	while (s_s2[++i])
	{
		cur = ft_strstr(cur, s_s2[i]);
		if (!cur)
		{
			ft_free_tab(&s_s2);
			return (0);
		}
	}
	if (s2[ft_strlen(s2) - 1] != '*')
	{
		if (s2[ft_strlen(s2) - 1] != s1[ft_strlen(s1) - 1])
		{
			ft_free_tab(&s_s2);
			return (0);
		}
	}
	ft_free_tab(&s_s2);
	return (1);
}

int				is_matching_star(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s2[i] != '*')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (!is_matching_star_bis(s2, s1, -1))
		return (0);
	return (1);
}

static int		check(char *s2, char *s1, size_t *i, size_t *j)
{
	while (s2[(*i)])
	{
		if (s2[(*i)] == '?')
		{
			(*i)++;
			(*j)++;
			continue ;
		}
		else if (s2[(*i)] == '*')
		{
			(*i)++;
			while (s2[(*i)] != s1[(*j)])
				(*j)++;
			continue ;
		}
		else if (s1[(*j)] && s1[(*j)] != s2[(*i)])
			return (0);
		(*i)++;
		(*j)++;
	}
	return (1);
}

int				is_matching_query(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*s;

	i = 0;
	j = 0;
	s = ft_strchr(s2, '*');
	if (s == NULL)
	{
		if (ft_strlen(s2) != ft_strlen(s1))
			return (0);
	}
	if (!check(s2, s1, &i, &j))
		return (0);
	if (s1[j] && s1[j] != s2[i])
		return (0);
	return (1);
}
