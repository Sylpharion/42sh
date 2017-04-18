/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 14:55:21 by ggobin            #+#    #+#             */
/*   Updated: 2017/01/28 14:55:21 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "Auto_completion/auto.h"

void		init_glob(char **end, char **cp, t_save *save)
{
	save->utils->aff_or_not = 0;
	ft_tab(save->utils, save);
	*end = ft_strdup(ft_strchr(save->line, '>'));
	*end = ft_strdup(ft_strchr(save->line, '<'));
	if (ft_strchr(save->line, '|'))
		*end = ft_strdup(ft_strchr(save->line, '|'));
	if (ft_strchr(save->line, '*'))
		*cp = ft_strsub(save->line, 0,
			ft_strchr(save->line, '*') - save->line);
	else
		*cp = ft_strdup(save->line);
	free(save->line);
	save->line = ft_strdup(*cp);
	free(*cp);
}
