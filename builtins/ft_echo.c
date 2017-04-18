/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:29:15 by afougere          #+#    #+#             */
/*   Updated: 2017/02/05 18:04:12 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh.h"

int			ft_check_echo(int *i, int *option, t_save *save, char **tab)
{
	if (!ft_strcmp(tab[*i], "$?"))
	{
		ft_putnbr_fd(WEXITSTATUS(save->last_state), save->fd);
		ft_putchar_fd('\n', save->fd);
		*save->exit_state = 0;
		return (1);
	}
	if (tab[*i][0] == '$')
		return (2);
	if (*i == 1 && !ft_strcmp(tab[*i], "-n"))
	{
		*option = 1;
		return (3);
	}
	return (0);
}

char		**ft_parse_echo(int *i, t_save *save)
{
	char **tab;
	char *sv;

	if (save->termio->yes == 1)
	{
		*i = -1;
		tab = ft_cp_env_to_tab(save->lst_heredoc);
		ft_change_dollar(&tab, &save->builts->env);
		ft_change_tilde(&tab, save->builts->env);
		sv = ft_split_stderr(tab, save, 0);
		ft_free_tab(&tab);
		tab = ft_strsplit(sv, ' ');
	}
	else
	{
		*i = 0;
		sv = ft_split_stderr(save->arg, save, 0);
		tab = ft_strsplit(sv, ' ');
	}
	free(sv);
	return (tab);
}

void		ft_pipe_chev(char **tab)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		if (ft_strchr(tab[i], '|') || ft_strchr(tab[i], '>'))
		{
			if (ft_strlen(tab[i]) == 1 || ft_strcmp(tab[i], ">>") == 0)
				tab[i] = NULL;
			else
			{
				tmp = tab[i];
				if (ft_strchr(tmp, '|'))
					tab[i] = ft_strsub(tmp, 0, ft_strchr(tmp, '|') - tmp);
				else
					tab[i] = ft_strsub(tmp, 0, ft_strchr(tmp, '>') - tmp);
				tab[i + 1] = NULL;
				free(tmp);
			}
		}
		i++;
	}
}

static void	ft_merde(int option, t_save *save)
{
	if (option == 0)
		ft_putchar_fd('\n', save->fd);
	*save->exit_state = 0;
}

void		ft_echo(t_save *save)
{
	int		i;
	int		option;
	int		ret;
	char	**tab;

	tab = ft_parse_echo(&i, save);
	ft_pipe_chev(tab);
	option = 0;
	ft_stderr(save, "echo");
	while (tab[++i])
	{
		ret = ft_check_echo(&i, &option, save, tab);
		if (ret == 2 || ret == 1)
			break ;
		else if (ret == 3)
			continue ;
		if (save->termio->yes == 1)
			ft_putchar_fd('\n', save->fd);
		ft_putstr_fd(tab[i], save->fd);
		if (tab[i + 1])
			ft_putchar_fd(' ', save->fd);
	}
	ft_free_tab(&tab);
	if (ret == 2 || ret == 0)
		ft_merde(option, save);
}
