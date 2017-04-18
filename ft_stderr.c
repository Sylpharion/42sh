/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stderr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:25:54 by afougere          #+#    #+#             */
/*   Updated: 2017/02/05 16:03:58 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	ft_stderr_bis(t_save *save, char *redir)
{
	int		i;

	i = 0;
	if (save->stder_bis && redir != NULL)
	{
		if (ft_strcmp(redir, "<<") ||
			(ft_strcmp(save->stder_bis, save->name_file) &&
			!ft_strcmp(redir, "<<")))
		{
			while (save->stder_bis && save->stder_bis[i + 1])
				i++;
			if (save->stder_bis[0] == '2' && save->stder_bis[i] == '1')
				dup2(1, 2);
			else if (save->stder_bis[0] == '1' && save->stder_bis[i] == '2')
				dup2(2, save->stdout_dup);
			else if (save->stder_bis[i] == '-')
				close(save->stder_bis[0] - 48);
		}
	}
}

void		ft_stderr(t_save *save, char *redir)
{
	int fd_bis;
	int j;

	j = 0;
	if (save->stder && save->stder[1])
	{
		if (!ft_strcmp(save->stder[0], "2>"))
		{
			fd_bis = open(save->stder[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd_bis, 2);
		}
		else if (!ft_strcmp(save->stder[0], "2>>"))
		{
			fd_bis = open(save->stder[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd_bis, 2);
		}
	}
	else
		ft_stderr_bis(save, redir);
}

static int	ft_init_stderr(char **tab, int *i, t_save *save)
{
	if (!ft_strcmp(tab[*i], "2>") || !ft_strcmp(tab[*i], "2>>"))
	{
		save->stder = (char **)malloc(sizeof(char *) * 3);
		save->stder[2] = NULL;
		save->stder[0] = ft_strdup(tab[*i]);
		save->stder[1] = ft_strdup(tab[(*i) + 1]);
		(*i) += 2;
		return (1);
	}
	else if (!ft_strncmp(&tab[*i][1], ">&", 2))
	{
		save->stder_bis = ft_strdup(tab[*i]);
		(*i)++;
		return (1);
	}
	return (0);
}

static void	free_if(t_save *save)
{
	if (save->stder != NULL)
	{
		ft_free_tab(&save->stder);
		save->stder = NULL;
	}
	if (save->stder_bis != NULL)
	{
		free(save->stder_bis);
		save->stder_bis = NULL;
	}
}

char		*ft_split_stderr(char **tab, t_save *save, int i)
{
	char	*sv;
	int		nb;

	nb = 0;
	free_if(save);
	sv = NULL;
	while (tab[i])
	{
		if (ft_init_stderr(tab, &i, save))
			;
		else
		{
			if (nb == 0)
				sv = ft_strdup(tab[i]);
			else
			{
				sv = ft_strjoin_free(sv, " ", 1);
				sv = ft_strjoin_free(sv, tab[i], 1);
			}
			nb++;
			i++;
		}
	}
	return (sv);
}
