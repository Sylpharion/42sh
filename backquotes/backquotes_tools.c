/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backquotes_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <ggobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 09:29:32 by ggobin            #+#    #+#             */
/*   Updated: 2017/01/23 11:42:59 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh.h"
#include "backquotes.h"

static void		remove_backquotes_escaped(char *str, int *i, int *u)
{
	if ((*u)++ % 2 == 0)
	{
		str[*i] = '|';
		str[(*i) + 1] = ' ';
	}
	else
	{
		u++;
		str[*i] = ' ';
		str[(*i) + 1] = ' ';
	}
}

void			*ft_remove_back_quotes(char *str)
{
	int		i;
	int		u;
	char	*p;

	i = -1;
	u = 0;
	if ((p = ft_strchr(str, '`')) == ft_strrchr(str, '`') && p != NULL)
	{
		p = ft_strsub(str, 0, ft_strlen(str - 1));
		while (str[++i])
			if (str[i] != '`')
				p[u++] = str[i];
		free(str);
		return (p);
	}
	while (str[++i])
	{
		if (str[i] == '\\' && str[i + 1] == '`')
			remove_backquotes_escaped(str, &i, &u);
		else if (str[i] == '`')
			str[i] = '\"';
	}
	return (str);
}

void			*ft_quotes_search(char *line)
{
	char	*start;
	char	*end;

	start = ft_strchr(line, '`');
	if (!start)
		return (strdup(line));
	end = ft_strrchr(start + 1, '`');
	if (!end)
		return (ft_strdup(start + 1));
	return (ft_strsub(line, start + 1 - line, end - (start + 1)));
}

static void		write_end(t_replace_string *rs, char const *cmd,
		char const *new, char const *old)
{
	rs->j = 0;
	rs->k = rs->i;
	while (new[rs->j])
	{
		rs->res[rs->i] = new[rs->j];
		(rs->j)++;
		(rs->i)++;
	}
	rs->l = 0;
	while (cmd[rs->k] && cmd[rs->k] == old[rs->l])
	{
		(rs->k)++;
		(rs->l)++;
	}
	while (cmd[rs->k])
	{
		rs->res[rs->i] = cmd[rs->k];
		(rs->k)++;
		(rs->i)++;
	}
	rs->res[rs->i] = 0;
}

char			*ft_replace_str_by_str(char *cmd, char *old, char *new)
{
	t_replace_string rs;

	rs.begin = ft_strstr(cmd, old);
	rs.res_size = ft_strlen(cmd) - ft_strlen(old) + ft_strlen(new);
	rs.res = (char *)malloc(sizeof(char) * rs.res_size + 1);
	rs.i = 0;
	while (&cmd[rs.i] < rs.begin)
	{
		rs.res[rs.i] = cmd[rs.i];
		rs.i++;
	}
	write_end(&rs, cmd, new, old);
	return (rs.res);
}
