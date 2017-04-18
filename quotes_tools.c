/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <ggobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 10:47:45 by ggobin            #+#    #+#             */
/*   Updated: 2017/02/06 10:36:29 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "operators.h"

int		ft_number_quote(char *save, char *str)
{
	int i;
	int j;

	i = -1;
	while (save && save[++i])
	{
		j = -1;
		while (str[++j])
		{
			if (str[j] == save[i])
			{
				i++;
				while (save[i] && str[j] != save[i])
					i++;
				if (save[i] == '\0')
					return (1);
			}
		}
	}
	return (0);
}

void	ft_copy(t_termio *termio, char c, t_save *save)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (termio->save[i])
	{
		if ((termio->save[i] != '\"' && termio->save[i] != '\'') ||
				(c && termio->save[i] != c))
		{
			save->line[j] = termio->save[i];
			j++;
		}
		else
		{
			if (c)
				c = 0;
			else
				c = termio->save[i];
		}
		i++;
	}
	save->line[j] = 0;
}

void	ft_copy_and_remove_quote(t_save *save, t_termio *termio,
t_parse_quotes *pq)
{
	int		i;
	int		nb;
	char	c;

	c = '\0';
	nb = 0;
	i = 0;
	if (save->line && ft_strlen(save->line) == 0)
		ft_putchar('\n');
	if (termio->save)
	{
		while (termio->save[i])
		{
			if (termio->save[i] != '\"' && termio->save[i] != '\'')
				nb++;
			i++;
		}
		free(save->line);
		save->line = (char *)malloc(sizeof(char) * (nb + 1));
		ft_copy(termio, c, save);
	}
	pq->s_semi = ft_strsplit(save->line, ';');
}
