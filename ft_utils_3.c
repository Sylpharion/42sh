/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 14:02:34 by afougere          #+#    #+#             */
/*   Updated: 2017/01/26 13:17:34 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtins/env.h"

static void		ft_dollar_bis(int i, int size, char ***tab, t_list *env)
{
	char	*sv;
	int		j;
	char	*cp;

	j = 1;
	sv = ft_strsub(&(*tab)[i][j], 0, size);
	if ((cp = ft_getenv(sv, env)))
	{
		free((*tab)[i]);
		(*tab)[i] = ft_strdup(cp);
	}
	free(sv);
}

void			ft_change_dollar(char ***tab, t_list **env)
{
	int		i;
	int		size;
	int		j;

	j = 1;
	size = 0;
	i = 0;
	while ((*tab)[i])
	{
		if ((*tab)[i][0] == '$')
		{
			while ((*tab)[i][j] && (*tab)[i][j] != '$')
			{
				j++;
				size++;
			}
			j = 1;
			ft_dollar_bis(i, size, tab, *env);
		}
		i++;
	}
}

static void		ft_tilde_bis(int i, char ***tab, t_list *env, char *str)
{
	char *sv;

	if ((sv = ft_getenv("HOME", env)))
	{
		free((*tab)[i]);
		if (ft_strlen(str) > 0)
			(*tab)[i] = ft_strjoin(sv, str);
		else
			(*tab)[i] = ft_strdup(sv);
	}
}

void			ft_change_tilde(char ***tab, t_list *env)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while ((*tab)[i])
	{
		if (!ft_strncmp((*tab)[i], "~", 1))
		{
			str = ft_strdup(ft_strchr((*tab)[i], '~') + 1);
			ft_tilde_bis(i, tab, env, str);
			free(str);
		}
		i++;
	}
}

char			*ft_fill_for_chev(t_save *save, t_list *lst)
{
	char	*sv;
	int		i;

	i = 0;
	sv = ft_strjoin(lst->content, " ");
	lst = lst->next;
	while (lst)
	{
		sv = ft_strjoin_free(sv, lst->content, 1);
		sv = ft_strjoin_free(sv, " ", 1);
		lst = lst->next;
	}
	while (save->arg_param[i])
		i++;
	i--;
	while (i >= 0)
	{
		sv = ft_strjoin_free(" ", sv, 2);
		sv = ft_strjoin_free(save->arg_param[i], sv, 2);
		i--;
	}
	ft_putendl("ici");
	return (sv);
}
