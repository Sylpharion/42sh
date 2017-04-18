/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queries.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:34:41 by ggobin            #+#    #+#             */
/*   Updated: 2016/12/13 13:34:56 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queries.h"

char			**init_queries(char **tmp, int i)
{
	t_queries	q;

	q.k = 0;
	q.count = 0;
	while (tmp[i][q.k])
	{
		if (tmp[i][q.k] == '?')
			q.count++;
		q.k++;
	}
	q.queries = (char **)malloc(sizeof(char *) * (q.count + 1));
	q.k = 0;
	q.count = 0;
	while (tmp[i][q.k])
	{
		if (tmp[i][q.k] == '?')
		{
			q.queries[q.count] = &tmp[i][q.k];
			*q.queries[q.count] = '*';
			q.count++;
		}
		q.k++;
	}
	q.queries[q.count] = NULL;
	return (q.queries);
}

void			delete_queries(char ***queries)
{
	size_t		k;
	char		**q;

	q = *queries;
	k = 0;
	while (q[k])
	{
		*q[k] = '?';
		k++;
	}
	free(*queries);
}
