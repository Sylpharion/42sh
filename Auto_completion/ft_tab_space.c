/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:37:39 by afougere          #+#    #+#             */
/*   Updated: 2017/02/01 14:29:51 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"
#include "../globing/globing.h"

static void	ft_no_begin_slash_bis(t_utils *utils, char *str, char *start,
				char *pwd)
{
	utils->glob.fmt = str;
	start = ft_strchr(str, '[');
	if (start && !check_pattern(str))
	{
		if (utils->glob.free_o_n == 2)
			utils->glob.free_o_n++;
		else
			utils->glob.free_o_n = 1;
		utils->glob.fmt = generate_combos(str);
	}
	ft_readdir(utils, pwd, str);
	free(pwd);
}

static void	ft_slash_or_no(int i, t_utils *utils, char **pwd, char **backup)
{
	char	*str;

	str = ft_strrchr(&utils->save[i], '/');
	if (str)
	{
		*pwd = ft_strjoin_free(*pwd, ft_strsub(utils->save, i,
		str - &utils->save[i]), 3);
		*backup = ft_strdup(str + 1);
		utils->glob.free_o_n = 2;
	}
	else
	{
		utils->glob.free_o_n = 2;
		*backup = ft_strdup(&utils->save[i]);
	}
}

char		*ft_no_begin_slash(char *pwd, t_utils *utils, int i, char *backup)
{
	char	*str;
	char	*start;

	start = NULL;
	utils->glob.free_o_n = 0;
	pwd = ft_strjoin_free(getcwd(NULL, 0), "/", 1);
	if (utils->save[ft_strlen(utils->save) - 1] == '/')
	{
		pwd = ft_strjoin_free(pwd, &utils->save[i], 1);
		str = ft_strrchr(pwd, '/');
		str++;
	}
	else
	{
		ft_slash_or_no(i, utils, &pwd, &backup);
		str = backup;
	}
	ft_no_begin_slash_bis(utils, str, start, pwd);
	return (backup);
}

static void	ft_parse_pwd(t_utils *utils, int i, char *pwd)
{
	char	*str;
	char	*start;
	int		j;

	j = 0;
	if (utils->save[i] == '/')
	{
		str = ft_strrchr(utils->save, '/') + 1;
		pwd = ft_strsub(utils->save, i, str - &utils->save[i]);
		utils->glob.fmt = str;
		start = ft_strchr(str, '[');
		if (start && !check_pattern(str))
		{
			j = 1;
			utils->glob.fmt = generate_combos(str);
		}
		ft_readdir(utils, pwd, str);
		if (j == 1)
			free(utils->glob.fmt);
		free(pwd);
	}
	else
		ft_backup_and_free(&utils, pwd, i);
}

void		ft_list_cmd_space(t_utils *utils)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = NULL;
	i = ft_strrchr(utils->save, ' ') - utils->save + 1;
	pwd = getcwd(NULL, 0);
	if (!utils->save[i])
		ft_readdir(utils, pwd, NULL);
	else
		ft_parse_pwd(utils, i, pwd);
	free(pwd);
}
