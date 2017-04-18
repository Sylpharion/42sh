/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queries.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:35:02 by ggobin            #+#    #+#             */
/*   Updated: 2016/12/13 13:35:16 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUERIES_H
# define QUERIES_H

# include "../Auto_completion/auto.h"

typedef struct		s_queries
{
	char			**queries;
	size_t			k;
	int				count;
}					t_queries;

char				**init_queries(char **tmp, int i);
void				delete_queries(char ***queries);

#endif
