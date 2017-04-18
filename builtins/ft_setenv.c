/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:22:23 by afougere          #+#    #+#             */
/*   Updated: 2017/01/31 18:49:33 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../sh.h"

char		*ft_init_ft_setenv(t_save *save)
{
	char *str;
	char **tmp;

	*save->exit_state = 0;
	tmp = NULL;
	if (ft_strchr(save->arg_semicolon[save->semi_i], '<'))
	{
		tmp = ft_strsplit(save->arg_semicolon[save->semi_i], '<');
		str = ft_strdup(tmp[0]);
	}
	else if ((ft_strchr(save->arg_semicolon[save->semi_i], '>')))
	{
		tmp = ft_strsplit(save->arg_semicolon[save->semi_i], '>');
		str = ft_strdup(tmp[0]);
	}
	else
		str = ft_strdup(save->arg_semicolon[save->semi_i]);
	if (tmp)
		ft_free_tab(&tmp);
	return (str);
}

void		ft_create_name_var(t_builts *builts, char *var)
{
	ft_list_reverse(&builts->env);
	ft_lstadd(&builts->env, ft_lstnew(var, ft_strlen(var) + 1));
	ft_list_reverse(&builts->env);
}

static int	ft_search_var_name(t_builts *builts, char *str, int len)
{
	t_list	*lst;

	lst = builts->env;
	while (lst)
	{
		if (!ft_strncmp(str, (char *)lst->content, len))
		{
			ft_change_env(lst, str);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

void		ft_setenv(t_save *save)
{
	char *str;
	char *name;
	char *equals;

	if (ft_check_option(save))
		return ;
	str = ft_init_ft_setenv(save);
	name = ft_strchr(str, ' ') + 1;
	if ((equals = ft_strchr(name, '=')))
	{
		if (ft_search_var_name(save->builts, name, equals - name + 1))
		{
			free(str);
			return ;
		}
		ft_create_name_var(save->builts, name);
	}
	else
	{
		*save->exit_state = 1;
		ft_putendl_fd("Syntax error", 2);
	}
	free(str);
}
