/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 11:07:04 by afougere          #+#    #+#             */
/*   Updated: 2016/09/27 11:56:20 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_invalid_command(char **tab)
{
	if (tab)
		ft_free_tab(&tab);
	ft_putendl("Invalid null command.");
	return (0);
}

int		ft_ambigous_input(char **tab)
{
	if (tab)
		ft_free_tab(&tab);
	ft_putendl("Ambigous input redirect.");
	return (0);
}

int		ft_ambigous_output(char **tab)
{
	if (tab)
		ft_free_tab(&tab);
	ft_putendl("Ambigous output redirect.");
	return (0);
}

int		ft_missing_name(char **tab)
{
	if (tab)
		ft_free_tab(&tab);
	ft_putendl("Missing name for redirect");
	return (0);
}

int		ft_syntax_error(char **tab)
{
	if (tab)
		ft_free_tab(&tab);
	ft_putendl("Syntax error stderr");
	return (0);
}
