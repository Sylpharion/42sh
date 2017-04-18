/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:40:00 by ggobin            #+#    #+#             */
/*   Updated: 2017/01/27 15:44:43 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operators.h"

static char	*copy_next(char **data, int i)
{
	size_t	j;
	char	*ret;

	j = i;
	ret = ft_strnew(1);
	while (data[j])
	{
		ret = ft_strjoin_free(ret, data[j], 1);
		ret = ft_strjoin_free(ret, " ", 1);
		j++;
	}
	return (ret);
}

int			check_and_or(char **data, t_save *save, char **next)
{
	size_t i;

	i = 0;
	while (data[i])
	{
		if (!ft_strncmp(data[i], "&&", 2))
		{
			save->next_operator = AND;
			*next = copy_next(data, i + 1);
			return (1);
		}
		else if (!ft_strncmp(data[i], "||", 2))
		{
			save->next_operator = OR;
			*next = copy_next(data, i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int			execute_if(int exit_state, enum e_operator condition)
{
	if ((WEXITSTATUS(exit_state) > 0 && condition == OR) ||
		(WEXITSTATUS(exit_state) == 0 && condition == AND) ||
		(exit_state == -1 && condition == NONE))
		return (1);
	else
		return (0);
}
