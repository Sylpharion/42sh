/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 15:07:56 by afougere          #+#    #+#             */
/*   Updated: 2017/01/31 12:32:29 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh.h"
#include "env.h"

char	*ft_getenv(char *str, t_list *lst)
{
	t_list	*tmp;
	char	**tab;

	tmp = lst;
	while (tmp)
	{
		tab = ft_strsplit((char const *)tmp->content, '=');
		if (!ft_strcmp(str, tab[0]))
		{
			ft_free_tab(&tab);
			return (ft_strchr((char const *)tmp->content, '=') + 1);
		}
		ft_free_tab(&tab);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_change_env(t_list *lst, char *str)
{
	if (lst)
	{
		free(lst->content);
		lst->content = NULL;
		lst->content = ft_strdup(str);
	}
}

void	ft_get_info_env(t_builts *builts)
{
	if (ft_getenv("PWD", builts->env))
	{
		if (builts->info_env->pwd)
			ft_strdel(&builts->info_env->pwd);
		builts->info_env->pwd = ft_strdup(ft_getenv("PWD", builts->env));
	}
	else if (ft_getenv("OLDPWD", builts->env))
	{
		if (builts->info_env->oldpwd)
			ft_strdel(&builts->info_env->oldpwd);
		builts->info_env->oldpwd = ft_strdup(ft_getenv("OLDPWD", builts->env));
	}
}

/*
** ___________________________________________________________
**| CD et CD -L sur dossier qui pointe sur un lien symbolique.|
**|___________________________________________________________|
*/

void	ft_pwd(t_builts *builts)
{
	char			*str;
	struct stat		stat_n;

	str = ft_getenv("PWD", builts->env);
	lstat(str, &stat_n);
	if (S_ISLNK(stat_n.st_mode))
		ft_putendl(str);
}

t_list	*ft_create_env(t_list *lst)
{
	char	*pwd;
	char	*oldpwd;
	char	*sv;

	pwd = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	pwd = ft_strjoin_free("PWD=", pwd, 2);
	if (((sv = ft_getenv("SHLVL", lst)) == NULL))
		ft_lstadd(&lst, ft_lstnew("SHLVL=1", 8));
	if (((sv = ft_getenv("PWD", lst)) == NULL))
		ft_lstadd(&lst, ft_lstnew(pwd, ft_strlen(pwd) + 1));
	if (((sv = ft_getenv("OLDPWD", lst)) == NULL))
		ft_lstadd(&lst, ft_lstnew(oldpwd, ft_strlen(oldpwd) + 1));
	if (((sv = ft_getenv("PATH", lst)) == NULL))
		ft_lstadd(&lst, ft_lstnew("PATH=/bin:/usr/bin", 19));
	free(pwd);
	free(oldpwd);
	return (lst);
}
