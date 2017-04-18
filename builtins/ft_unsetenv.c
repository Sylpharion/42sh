/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:22:34 by afougere          #+#    #+#             */
/*   Updated: 2017/02/05 08:31:49 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../sh.h"

static void	ft_remove_var(t_list **lst, char *remove)
{
	t_list	*tmp;
	int		len;

	tmp = *lst;
	len = ft_strlen(remove);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, remove, len) == 0 &&
				((char *)tmp->content)[len] == '=')
		{
			if (tmp == *lst)
			{
				remove_elem(&tmp);
				*lst = tmp;
			}
			else
				remove_elem(&tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

static char	*ft_parse_unsetenv(t_save *save)
{
	char *str;
	char *tmp_bis;

	str = NULL;
	if (ft_strstr(save->arg_semicolon[save->semi_i], "<"))
		str = *ft_strsplit(save->arg_semicolon[save->semi_i], '<');
	else if (ft_strstr(save->arg_semicolon[save->semi_i], ">"))
		str = *ft_strsplit(save->arg_semicolon[save->semi_i], '>');
	if (str && ft_strchr(str, ' '))
		tmp_bis = ft_strchr(str, ' ') + 1;
	else if (str)
		tmp_bis = str;
	else if (ft_strchr(save->arg_semicolon[save->semi_i], ' '))
		tmp_bis = ft_strchr(save->arg_semicolon[save->semi_i], ' ') + 1;
	else
		tmp_bis = save->arg_semicolon[save->semi_i];
	free(str);
	if (tmp_bis[0] == '-')
	{
		ft_putstr_fd("unsetenv: ", 2);
		write(2, tmp_bis, 2);
		ft_putendl_fd(": invalid option", 2);
		return (NULL);
	}
	return (tmp_bis);
}

void		ft_unsetenv(t_save *save)
{
	t_list	*tmp;
	char	*tmp_bis;
	char	**vars;
	int		i;

	*save->exit_state = 0;
	tmp_bis = ft_parse_unsetenv(save);
	if (tmp_bis == NULL)
		return ;
	tmp = save->builts->env;
	if (ft_strchr(tmp_bis, ' '))
	{
		vars = ft_strsplit(tmp_bis, ' ');
		i = 0;
		while (vars[i])
		{
			ft_remove_var(&tmp, vars[i]);
			i++;
		}
		ft_free_tab(&vars);
	}
	else
		ft_remove_var(&tmp, tmp_bis);
	save->builts->env = tmp;
}
