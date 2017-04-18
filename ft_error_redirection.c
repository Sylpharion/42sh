/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 14:46:53 by afougere          #+#    #+#             */
/*   Updated: 2017/01/25 15:06:55 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_back_chev(char *str, int i, int nb)
{
	if (ft_strchr(str, '<'))
	{
		while (str[i])
		{
			if (str[i] == '<' && str[i + 1] != '<')
			{
				nb++;
				i++;
				if (str[i] == '\0')
					return (ft_missing_name(NULL));
				while (ft_isalpha(str[i]) == 0 || str[i] == '<')
					i++;
			}
			if (nb > 1)
				return (ft_ambigous_output(NULL));
			i++;
		}
	}
	return (1);
}

static int	ft_error_pipe(char *str, int i)
{
	char **tab;
	char **tab_bis;

	tab_bis = NULL;
	tab = NULL;
	if (ft_strchr(str, '|'))
	{
		while (str[++i])
		{
			if (str[i] == '|')
			{
				i++;
				if (str[i] == '\0')
					return (ft_invalid_command(tab));
				while (ft_isalpha(str[++i]) == 0)
					;
			}
		}
		tab = ft_strsplit(str, '|');
		if (!ft_error_pipe_chev(tab, 0))
			return (0);
		ft_free_tab(&tab);
	}
	return (1);
}

static int	ft_error_chev(char *str, int i, int nb)
{
	char	**tab;
	int		j;

	j = 0;
	tab = ft_strsplit(str, ' ');
	if (ft_strchr(str, '>'))
	{
		i = -1;
		while (tab[++i])
		{
			if ((!ft_strcmp(tab[i], ">") || !ft_strcmp(tab[i], ">>")))
			{
				nb++;
				if ((!ft_strcmp(tab[i], ">") || !ft_strcmp(tab[i], ">>"))
						&& tab[i + 1] == NULL)
					return (ft_missing_name(tab));
			}
			if (nb > 1 || j > 1)
				return (ft_ambigous_output(tab));
		}
	}
	ft_free_tab(&tab);
	return (1);
}

static int	ft_error_stderr(char *str, int i)
{
	char **tab;

	tab = ft_strsplit(str, ' ');
	while (tab[i])
	{
		if ((!ft_strcmp(tab[i], "2>") && tab[i + 1] == NULL) ||
				(!ft_strcmp(tab[i], "2>>") && tab[i + 1] == NULL) ||
				(!ft_strcmp(tab[i], "2>&1") && tab[i - 1] == NULL))
			return (ft_syntax_error(tab));
		if (tab[i][0] == '>' && !ft_strcmp(tab[i + 1], "2>&1"))
			return (ft_syntax_error(tab));
		if (tab[i][0] == '>' && (!ft_strcmp(tab[i + 1], "2>") ||
					!ft_strcmp(tab[i + 1], "2>>")))
			return (ft_missing_name(tab));
		i++;
	}
	ft_free_tab(&tab);
	return (1);
}

int			ft_error_redirection(char *str)
{
	if (str[0] == '|' || str[0] == '>' || (str[0] == '<' && str[1] != '<'))
		return (ft_invalid_command(NULL));
	if (!ft_error_pipe(str, -1))
		return (0);
	if (!ft_back_chev(str, 0, 0))
		return (0);
	if (!ft_error_chev(str, 0, 0))
		return (0);
	if (!ft_error_stderr(str, 0))
		return (0);
	return (1);
}
