/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:28:58 by afougere          #+#    #+#             */
/*   Updated: 2017/02/05 09:51:10 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh.h"
#include "env.h"
#include "cd.h"

int		ft_cd_from_env(t_list *env, t_list *pwd, char const *key,
		char const *cmpl)
{
	char *next_dir;
	char *tmp;

	while (env)
	{
		if (!ft_strncmp(env->content, key, ft_strlen(key)))
		{
			if (cmpl)
				next_dir = ft_strjoin(ft_strchr(env->content, '=') + 1, cmpl);
			else
				next_dir = ft_strchr(env->content, '=') + 1;
			if (chdir(next_dir))
				return (write(2, "Directory not found.\n", 21));
			if (cmpl)
				free(next_dir);
			tmp = ft_strjoin_free("PWD=", getcwd(NULL, 0), 2);
			ft_change_env(pwd, tmp);
			free(tmp);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

t_list	*get_env_var_by_name(char const *name, t_list *env)
{
	while (env)
	{
		if (!ft_strncmp(env->content, name, ft_strlen(name)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	chdir_and_update_env(t_save *save, char **cwd_cmpl, t_list **pwds,
														char const *env_var)
{
	if (ft_cd_from_env(save->builts->env, pwds[0], env_var, cwd_cmpl[1]))
	{
		write(2, env_var, ft_strlen(env_var) - 1);
		write(2, " not set in environment.\n", 25);
		*save->exit_state = 1;
		free(cwd_cmpl[0]);
		return ;
	}
	cwd_cmpl[0] = ft_strjoin_free("OLDPWD=",
			cwd_cmpl[0] == NULL ? ft_strdup("") : cwd_cmpl[0], 2);
	ft_change_env(pwds[1], cwd_cmpl[0]);
	free(cwd_cmpl[0]);
}

int		simple_chdir(char *args, t_cd *cd, char flag)
{
	if (!args)
		return (1);
	if (!ft_strcmp(ft_strchr(cd->pwds[0]->content, '=') + 1, "/") &&
			!ft_strcmp(args, ".."))
		cd->next_dir = ft_strdup(ft_strrchr(args, '.') + 1);
	if (args[0] != '/')
	{
		if (cd->next_dir)
			free(cd->next_dir);
		cd->str_tmp = ft_strjoin("/", args);
		cd->next_dir = ft_strjoin_free(getcwd(NULL, 0), cd->str_tmp, 1);
		free(cd->str_tmp);
	}
	else
		cd->next_dir = ft_strdup(cd->args);
	if (!chdir(cd->next_dir))
		check_file_stats(cd, flag);
	else
	{
		write(2, "Directory not found.\n", 21);
		free(cd->cwd_cmpl[0]);
		free(cd->next_dir);
	}
	return (1);
}

void	ft_cd(t_save *save)
{
	t_cd	cd;

	*save->exit_state = 0;
	cd.next_dir = NULL;
	cd.pwds[0] = get_env_var_by_name("PWD=", save->builts->env);
	cd.pwds[1] = get_env_var_by_name("OLDPWD=", save->builts->env);
	cd.cwd_cmpl[0] = getcwd(NULL, 0);
	if (cd.pwds[0] && cd.cwd_cmpl[0] && ft_strcmp(cd.cwd_cmpl[0],
												&(cd.pwds[0]->content[4])))
	{
		free(cd.cwd_cmpl[0]);
		cd.cwd_cmpl[0] = ft_strdup(&(cd.pwds[0]->content[4]));
	}
	cd.cwd_cmpl[1] = NULL;
	cd.args = ft_strchr(save->arg_semicolon[save->semi_i], ' ');
	check_parameters(&cd, save);
}
