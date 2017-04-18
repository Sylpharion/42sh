/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 13:43:56 by afougere          #+#    #+#             */
/*   Updated: 2017/02/02 12:16:43 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh.h"
#include "env.h"

void	ft_change_prompt(char *tmp, t_save *save, t_list **lst)
{
	char	*pwd;

	pwd = ft_getenv("PWD", save->builts->env);
	if (tmp)
	{
		if (tmp && ft_strcmp(tmp, pwd))
		{
			free(save->termio->prompt);
			save->termio->prompt = ft_prompt();
			save->termio->prompt_len = ft_strlen(save->termio->prompt) - 41;
		}
		free(tmp);
	}
	else
	{
		pwd = ft_strjoin_free("PWD=", getcwd(NULL, 0), 2);
		ft_create_name_var(save->builts, pwd);
		ft_change_prompt(pwd, save, lst);
	}
}
