/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_enter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 12:29:08 by afougere          #+#    #+#             */
/*   Updated: 2017/02/19 11:26:38 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_return(t_termio *termio, t_list *sv)
{
	t_list *s;

	s = NULL;
	if (termio->history && termio->history->prev != NULL)
	{
		ft_home_end(((t_list **)(&termio->history->content)), termio, 70);
		s = (t_list *)malloc(sizeof(t_list));
		s->content = ft_cp_env_to_sv(((t_list **)(&termio->history->content)));
		ft_lst_free(((t_list **)(&termio->history->content)));
		termio->history->content = ft_cp_env_to_sv(&termio->cp);
		s->next = NULL;
		s->prev = NULL;
		remove_elem(&sv);
		ft_lstadd(&sv, s);
		termio->history = sv;
	}
	else if (termio->history && ft_list_size(termio->history->content) == 0)
		remove_elem(&termio->history);
	ft_home_end(((t_list **)(&termio->history->content)), termio, 70);
	return (0);
}

void	ft_put_buffer(char buffer[1024], t_termio *termio, t_save *save)
{
	size_t	cc;
	int		fd;

	fd = open("/dev/tty", O_NOCTTY | O_WRONLY);
	if (buffer[0] >= 32 && buffer[0] < 127)
	{
		cc = 0;
		while (cc < ft_strlen(buffer))
		{
			termio->i++;
			termio->size++;
			if (insert_elem(((t_list **)(&termio->history->content)),
			buffer[cc], save, termio))
				ft_putchar_fd(buffer[cc], fd);
			cc++;
		}
	}
	close(fd);
}

void	ft_word_cut_copy_term(char buffer[1024], t_termio *termio, t_save *save)
{
	if (buffer[5] == 68 || buffer[5] == 67)
		ft_word(buffer[5], termio);
	if (buffer[0] == 21 || buffer[0] == 11 || buffer[0] == 16)
		ft_cut_copy_paste(save, termio, buffer[0]);
}

int		outc(int c)
{
	write(1, &c, 1);
	return (c);
}
