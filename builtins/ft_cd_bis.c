/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 12:04:07 by afougere          #+#    #+#             */
/*   Updated: 2017/02/05 09:51:34 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh.h"
#include "env.h"
#include "cd.h"

static void	check_link(char flag, t_cd *cd, struct stat *buf)
{
	if (flag == 'P' || flag == 0)
	{
		if (flag == 0)
		{
			if (!lstat(cd->next_dir, buf))
			{
				if (S_ISLNK(buf->st_mode))
				{
					free(cd->str_tmp);
					cd->str_tmp = ft_strjoin_free("PWD=", cd->next_dir, 2);
				}
				else
					free(cd->next_dir);
			}
		}
		else
			free(cd->next_dir);
	}
	else
	{
		free(cd->str_tmp);
		cd->str_tmp = ft_strjoin_free("PWD=", cd->next_dir, 2);
	}
}

int			check_file_stats(t_cd *cd, char flag)
{
	struct stat buf;

	cd->str_tmp = ft_strjoin_free("PWD=", getcwd(NULL, 0), 2);
	check_link(flag, cd, &buf);
	ft_change_env(cd->pwds[0], cd->str_tmp);
	free(cd->str_tmp);
	cd->cwd_cmpl[0] = ft_strjoin_free("OLDPWD=", cd->cwd_cmpl[0], 2);
	cd->cwd_cmpl[0] = (cd->cwd_cmpl[0] == NULL) ?
										ft_strdup("OLDPWD=") : cd->cwd_cmpl[0];
	ft_change_env(cd->pwds[1], cd->cwd_cmpl[0]);
	free(cd->cwd_cmpl[0]);
	return (0);
}

void		check_parameters(t_cd *cd, t_save *save)
{
	if (cd->args == NULL || (cd->args[1] == '~' && cd->args[2] == 0))
	{
		chdir_and_update_env(save, cd->cwd_cmpl, cd->pwds, "HOME=");
		ft_change_prompt(cd->pwds[0] != NULL ?
			ft_strdup(cd->pwds[0]->content) : NULL, save, (t_list **)NULL);
		return ;
	}
	cd->args++;
	if (*(cd->args) == '-' && cd->args[1] == 0)
		chdir_and_update_env(save, cd->cwd_cmpl, cd->pwds, "OLDPWD=");
	else if (*(cd->args) == '-' && (cd->args[1] == 'L' || cd->args[1] == 'P'))
		simple_chdir(ft_strchr(&(cd->args[1]), ' ') + 1, cd, cd->args[1]);
	else if (*(cd->args) == '~' && cd->args[1] == '/')
	{
		cd->cwd_cmpl[1] = &cd->args[1];
		chdir_and_update_env(save, cd->cwd_cmpl, cd->pwds, "HOME=");
	}
	else
	{
		if (simple_chdir(cd->args, cd, 0))
			*save->exit_state = 1;
	}
	ft_change_prompt(cd->pwds[0] != NULL ?
		ft_strdup(cd->pwds[0]->content) : NULL, save, (t_list **)NULL);
}
