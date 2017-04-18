/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_by_word_left.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelauna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:50:08 by mdelauna          #+#    #+#             */
/*   Updated: 2017/01/25 15:29:01 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	ft_word_left(t_list **sv, int *i)
{
	t_list	*sv_bis;
	int		i_bis;

	sv_bis = *sv;
	i_bis = *i;
	while (*sv && (*sv)->next && *(char *)(*sv)->content != ' ')
	{
		(*i)++;
		*sv = (*sv)->next;
	}
	while (*sv && (*sv)->next && *(char *)(*sv)->content == ' ')
	{
		(*i)++;
		*sv = (*sv)->next;
	}
	if (*sv && (*sv)->next == NULL)
	{
		(*i) = i_bis;
		*sv = sv_bis;
	}
}

static void	ft_replace_curser(int *i, t_termio *termio, t_list *sv)
{
	if (sv)
	{
		if (*i > 1)
		{
			while (--(*i) > 0)
			{
				termio->i--;
				tputs(tgetstr("le", NULL), 1, outc);
			}
		}
	}
}

void		ft_word(char buffer, t_termio *termio)
{
	t_list	*sv;
	int		i;

	i = 1;
	if (buffer == 68 && termio->history->content)
	{
		sv = termio->history->content;
		if (sv->next)
		{
			ft_word_left(&sv, &i);
			ft_replace_curser(&i, termio, sv);
		}
		termio->history->content = sv;
	}
	else if (buffer == 67 && termio->history->content)
		ft_word_right(termio);
}
