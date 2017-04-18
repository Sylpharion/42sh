/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 10:33:03 by afougere          #+#    #+#             */
/*   Updated: 2017/01/24 15:47:51 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "operators.h"
#include "builtins/env.h"
#include "backquotes/backquotes.h"

static void	browse_them_all(t_parse_quotes *pq, t_save *save, size_t *j)
{
	char	*tmp;

	while (pq->s_semi[*j])
	{
		if (ft_strchr(pq->s_semi[*j], '`'))
		{
			tmp = pq->s_semi[*j];
			pq->s_semi[*j] =
				ft_exec_back_quotes(pq->s_semi[*j], save->launched_path);
			free(tmp);
		}
		ft_split_by_operators(pq, save, *j);
		if (pq->op)
		{
			free(pq->s_semi[*j]);
			pq->s_semi[*j] = ft_strdup(pq->next);
			ft_strdel(&pq->next);
			ft_free_tab(&pq->s_space);
			pq->op = 0;
			continue ;
		}
		(*j)++;
		save->last_state = *save->exit_state;
		ft_init_state(save);
	}
}

void		ft_parse_quotes_and_exec(t_save *save, t_termio *termio)
{
	t_parse_quotes	pq;
	size_t			j;

	if (save->line && ft_init_parser(termio, &pq.s_space, save, &j) == 0)
	{
		ft_copy_and_remove_quote(save, termio, &pq);
		browse_them_all(&pq, save, &j);
		ft_free_tab(&pq.s_space);
		ft_free_tab(&pq.s_semi);
	}
}

void		ft_change_env_save(t_save *save, char **envp)
{
	save->termio->save_cut = NULL;
	ft_get_env_lst(envp, save->builts);
	save->builts->env = ft_create_env(save->builts->env);
	ft_change_shlvl(save);
	ft_putstr(save->termio->prompt);
}
