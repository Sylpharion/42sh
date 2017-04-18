/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:40:43 by afougere          #+#    #+#             */
/*   Updated: 2017/02/03 15:51:10 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh.h"
#include "env.h"

void		ft_aff_var(t_builts *builts, char **tab, int i)
{
	while (tab[i])
	{
		if (!ft_getenv(tab[i], builts->env))
		{
			ft_putstr("setenv: no variable named: ");
			ft_putendl(tab[i]);
			return ;
		}
		ft_putstr("typeset -x ");
		ft_putstr(tab[i]);
		ft_putchar('=');
		ft_putendl(ft_getenv(tab[i], builts->env));
		i++;
	}
}

void		ft_option_setenv(t_builts *builts)
{
	t_list *tmp;

	tmp = builts->env;
	ft_list_sort(&tmp, ft_strcmp);
	while (tmp)
	{
		if (((char *)tmp->content)[0] == '_')
		{
			tmp = tmp->next;
			continue ;
		}
		ft_putstr("declare -x ");
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
}

static void	ft_check_option2(t_save *save)
{
	char	*tmp;

	if (ft_strchr(save->arg_semicolon[save->semi_i], ' '))
	{
		tmp = ft_strchr(save->arg_semicolon[save->semi_i], ' ');
		free(save->arg_semicolon[save->semi_i]);
		save->arg_semicolon[save->semi_i] = ft_strjoin("env ", tmp);
		ft_chevron(save, save->arg_semicolon[save->semi_i], 0);
	}
	else
	{
		free(save->arg_semicolon[save->semi_i]);
		save->arg_semicolon[save->semi_i] = ft_strdup("env");
		ft_env(save);
	}
}

int			ft_check_option(t_save *save)
{
	int		i;

	i = 0;
	while (save->arg[i])
	{
		if (!ft_strcmp(save->arg[i], "-p"))
		{
			if (!save->arg[i + 1])
				ft_option_setenv(save->builts);
			else
				ft_aff_var(save->builts, save->arg, i + 1);
			return (1);
		}
		i++;
	}
	if (i == 1 || (save->arg[1] && !ft_strncmp(save->arg[1], ">", 1)))
	{
		ft_check_option2(save);
		return (1);
	}
	return (0);
}

t_list		*ft_check_option_cd(t_builts *builts, t_save *s)
{
	t_list	*lst;
	int		i;

	i = 0;
	lst = NULL;
	while (s->arg && s->arg[i])
	{
		if (!ft_strcmp(s->arg[i], "-P") || !ft_strcmp(s->arg[i], "-PL"))
			builts->option->cd_p = 1;
		else if (!ft_strcmp(s->arg[i], "-L") || !ft_strcmp(s->arg[i], "-LP"))
			builts->option->cd_l = 1;
		else if (s->arg[i][0] == '-' && (s->arg[i][1] != 'P' ||
					s->arg[i][1] != 'L') && s->arg[i][1] != 0)
		{
			ft_putstr_fd("cd: ", 2);
			write(2, s->arg[i], 2);
			ft_putendl_fd(": invalid option", 2);
		}
		else
			ft_lstadd(&lst, ft_lstnew(s->arg[i], ft_strlen(s->arg[i]) + 1));
		i++;
	}
	ft_list_reverse(&lst);
	return (lst);
}
