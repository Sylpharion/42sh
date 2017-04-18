/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:25:44 by afougere          #+#    #+#             */
/*   Updated: 2017/01/24 16:04:22 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_save	*singleton(void)
{
	static t_save kaka;

	return (&kaka);
}

void	sign(int sig)
{
	t_save *save;

	(void)sig;
	save = singleton();
	if (save->termio->yes != 2)
		ft_putchar('\n');
	if (ft_jj(-1) != 1)
		ft_putstr(save->termio->prompt);
	save->termio->i = save->termio->prompt_len;
	save->termio->size = save->termio->prompt_len;
	if (save->termio->history)
		ft_lst_free(((t_list **)(&save->termio->history->content)));
	if (save->termio->yes == 2)
		free(save->line);
	ft_jj(3);
	if (save->termio->yes == 1 || save->termio->yes == 2)
		exit(0);
}

int		ft_ctrl_d(char buffer[1024], t_termio *termio, t_save *save)
{
	if (buffer[0] == 4 && termio->heredoc == 1)
	{
		ft_lst_to_str(termio->history->content, save, termio);
		termio->ctrl_d_heredoc = NULL;
		termio->ctrl_d_heredoc = ft_strdup(save->name_file);
		return (2);
	}
	else if (buffer[0] == 4)
	{
		ft_lst_to_str(termio->history->content, save, termio);
		if (ft_strlen(save->line) > 0)
			return (0);
		ft_putendl("exit");
		exit(0);
	}
	return (0);
}

int		ft_jj(int i)
{
	static int enter = 0;

	if (i != -1)
		enter = i;
	return (enter);
}
