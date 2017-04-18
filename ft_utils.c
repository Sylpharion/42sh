/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:04:37 by afougere          #+#    #+#             */
/*   Updated: 2017/01/25 15:11:02 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "Auto_completion/auto.h"
#include "globing/globing.h"
#include "builtins/env.h"

void	ft_replace_car(char *str, char c, char b)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == c)
				str[i] = b;
			i++;
		}
	}
}

t_list	*ft_cp_envp(char **envp)
{
	t_list	*envp_cp;

	envp_cp = NULL;
	while (*envp)
	{
		ft_lstadd(&envp_cp, ft_lstnew(*envp, ft_strlen(*envp) + 1));
		envp++;
	}
	envp_cp = ft_create_env(envp_cp);
	ft_list_reverse(&envp_cp);
	return (envp_cp);
}

char	**ft_cp_env_to_tab(t_list *env)
{
	t_list	*sv;
	char	**cp_env;
	int		size;
	int		i;

	i = 0;
	size = 0;
	sv = env;
	while (env)
	{
		size++;
		env = env->next;
	}
	env = sv;
	cp_env = (char **)malloc(sizeof(char *) * (size + 1));
	cp_env[size] = NULL;
	while (env)
	{
		cp_env[i] = ft_strdup(env->content);
		i++;
		env = env->next;
	}
	env = sv;
	return (cp_env);
}
