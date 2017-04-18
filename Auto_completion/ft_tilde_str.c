/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tilde_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelauna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 16:12:57 by mdelauna          #+#    #+#             */
/*   Updated: 2017/01/31 16:19:14 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/env.h"
#include "auto.h"

static char	*ft_tilde_str2(char *cp)
{
	char	*pp;

	pp = NULL;
	if (ft_strchr(cp, '>') || ft_strchr(cp, '|') || ft_strchr(cp, '<'))
	{
		if (ft_strchr(cp, '<'))
			pp = ft_strsub(cp, 0, ft_strchr(cp, '<') - cp);
		else if (ft_strchr(cp, '|'))
			pp = ft_strsub(cp, 0, ft_strchr(cp, '|') - cp);
		else if (ft_strchr(cp, '>'))
			pp = ft_strsub(cp, 0, ft_strchr(cp, '>') - cp);
		free(cp);
		cp = ft_strtrim(pp);
		free(pp);
	}
	return (cp);
}

char		*ft_tilde_str(char *str, t_save *save)
{
	char	*tmp;
	int		i;
	char	*cp;
	char	*tmp_bis;

	i = 0;
	tmp_bis = NULL;
	if (ft_strchr(str, '~'))
	{
		while (str[i] != '~')
			i++;
		tmp_bis = (char *)malloc(sizeof(char) * i + 1);
		tmp_bis = ft_strncpy(tmp_bis, str, i);
		tmp_bis[i] = 0;
		tmp = ft_strsub(str, i + 1, ft_strlen(&str[i]));
		cp = ft_strjoin(tmp_bis, ft_getenv("HOME", save->builts->env));
		cp = ft_strjoin_free(cp, tmp, 3);
		cp = ft_strjoin_free(cp, "/", 1);
		return (cp);
	}
	else
		cp = ft_strdup(str);
	cp = ft_tilde_str2(cp);
	return (cp);
}
