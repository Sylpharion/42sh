/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 10:38:51 by afougere          #+#    #+#             */
/*   Updated: 2017/01/31 13:25:24 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh.h"
#include "env.h"

void	ft_no_file(t_save *save, char *str)
{
	ft_putstr_fd("cd: No such file or directory: ", 2);
	if (ft_strrchr(str, '/'))
		ft_putendl_fd(ft_strrchr(str, '/') + 1, 2);
	else
		ft_putendl_fd(str, 2);
	*save->exit_state = 1;
}

int		ft_error_home(t_builts *builts, char *str)
{
	if (!ft_getenv("HOME", builts->env))
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (0);
	}
	if (access(ft_getenv("HOME", builts->env), F_OK | X_OK) != 0)
	{
		ft_putstr_fd("cd: No such file or directory: ", 2);
		ft_putendl_fd(str, 2);
		return (0);
	}
	return (1);
}

void	ft_change_var(t_list *lst, char *link_pwd, char *tmp_link_pwd,
						t_list *tmp)
{
	int				cmp;
	char			*new_pwd;
	char			*pwd;
	struct stat		stat_n;
	char			*tmp_link;

	(void)tmp_link_pwd;
	tmp_link = ft_strdup(ft_getenv("OLDPWD", tmp));
	lstat(tmp_link, &stat_n);
	pwd = getcwd(NULL, 0);
	cmp = ft_strncmp(tmp->content, "PWD=", 4);
	new_pwd = NULL;
	if (lst && lst->next && !ft_strcmp(lst->next->content, "-") &&
		!cmp && !link_pwd && S_ISLNK(stat_n.st_mode))
		new_pwd = ft_strjoin("PWD=", tmp_link);
	else if (!cmp && !link_pwd)
		new_pwd = ft_strjoin("PWD=", pwd);
	else if (!cmp && link_pwd)
		new_pwd = ft_strjoin("PWD=", link_pwd);
	ft_change_env(tmp, new_pwd);
	free(pwd);
	free(tmp_link);
	free(new_pwd);
}
