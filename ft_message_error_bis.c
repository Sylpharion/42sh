/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message_error_bis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:24:15 by afougere          #+#    #+#             */
/*   Updated: 2016/12/13 13:24:16 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_error_pipe_chev(char **tab, int i)
{
	char **tab_bis;

	tab_bis = NULL;
	tab_bis = ft_strsplit(tab[0], ' ');
	while (tab_bis[i])
	{
		if (!ft_strcmp(tab_bis[i], ">"))
		{
			ft_free_tab(&tab_bis);
			return (ft_ambigous_output(tab));
		}
		i++;
	}
	if (ft_strchr(tab[1], '<'))
	{
		ft_free_tab(&tab_bis);
		return (ft_ambigous_input(tab));
	}
	ft_free_tab(&tab_bis);
	return (1);
}
