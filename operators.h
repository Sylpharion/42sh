/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <ggobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:38:38 by ggobin            #+#    #+#             */
/*   Updated: 2017/01/24 16:21:12 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
# define OPERATORS_H

# include "sh.h"

typedef struct		s_parse_quotes
{
	char			**s_semi;
	char			**s_space;
	char			*next;
	size_t			j;
	size_t			k;
	int				op;
}					t_parse_quotes;

/*
** quotes_tools.c
*/
int					ft_number_quote(char *save, char *str);
void				ft_copy(t_termio *termio, char c, t_save *save);
void				ft_copy_and_remove_quote(t_save *save,
					t_termio *termio, t_parse_quotes *pq);
void				ft_copy_and_remove_quote(t_save *save, t_termio *termio,
					t_parse_quotes *pq);

/*
** operators.c
*/
int					check_and_or(char **data, t_save *save, char **next);
int					execute_if(int exit_state, enum e_operator condition);

/*
** ft_logic_operator.c
*/
void				ft_init_state(t_save *save);
int					ft_init_parser(t_termio *termio, char ***s_space,
					t_save *save, size_t *j);
void				ft_split_by_operators(t_parse_quotes *pq, t_save *save,
					int j);

#endif
