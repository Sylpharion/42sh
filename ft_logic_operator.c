/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <ggobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 10:39:32 by ggobin            #+#    #+#             */
/*   Updated: 2017/02/05 08:24:41 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "operators.h"

void		ft_init_state(t_save *save)
{
	*save->exit_state = -1;
	save->last_operator = NONE;
	save->next_operator = NONE;
}

static int	ft_fill_termio_save(t_termio *termio, t_save *save)
{
	int		i;
	char	c;

	i = 0;
	while (termio->save[i] != 34 && termio->save[i] != 39)
		i++;
	c = termio->save[i];
	termio->quote = save->termio->prompt_len;
	save->termio->prompt_len = 2;
	termio->yes = 2;
	while (1)
	{
		ft_putstr("\n> ");
		ft_term(save, termio);
		termio->save = ft_strjoin_free(termio->save, "\n", 1);
		termio->save = ft_strjoin_free(termio->save, save->line, 1);
		if (c == termio->save[ft_strlen(termio->save) - 1])
		{
			save->termio->prompt_len = termio->quote;
			termio->quote = 1;
			return (0);
		}
	}
	return (1);
}

int			ft_init_parser(t_termio *termio, char ***s_space,
t_save *save, size_t *j)
{
	*j = 0;
	ft_init_for_quotes(termio, save, s_space);
	if (ft_number_quote(termio->save, "\'\"") == 1)
	{
		ft_jj(1);
		termio->pid = fork();
		if (termio->pid == 0 && ft_fill_termio_save(termio, save) == 0)
		{
			ft_putchar('\n');
			return (0);
		}
		else
			wait(NULL);
	}
	else
	{
		if (save->line && ft_strlen(save->line) > 0 &&
		ft_strlen(save->termio->prompt) > 0)
			ft_putchar('\n');
		return (0);
	}
	save->fail_quotes = 1;
	return (0);
}

static void	fill_save_operators(t_save *save, t_parse_quotes *pq)
{
	free(save->line);
	save->line = ft_strnew(1);
	pq->k = 0;
	while (pq->s_space[pq->k + 1])
	{
		if (!ft_strcmp(pq->s_space[pq->k + 1], "&&") ||
			!ft_strcmp(pq->s_space[pq->k + 1], "||"))
			break ;
		save->line = ft_strjoin_free(save->line, pq->s_space[pq->k++], 1);
		save->line = ft_strjoin_free(save->line, " ", 1);
	}
	save->line = ft_strjoin_free(save->line, pq->s_space[pq->k], 1);
}

void		ft_split_by_operators(t_parse_quotes *pq, t_save *save, int j)
{
	if (pq->s_space)
		ft_free_tab(&pq->s_space);
	pq->s_space = ft_strsplit(pq->s_semi[j], ' ');
	pq->op = check_and_or(pq->s_space, save, &pq->next);
	if (ft_strstr(pq->s_semi[j], "&&") ||
	ft_strstr(pq->s_semi[j], "||"))
		fill_save_operators(save, pq);
	else
	{
		free(save->line);
		save->line = ft_strdup(pq->s_semi[j]);
	}
	loop(save, -1);
}
