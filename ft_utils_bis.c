/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:26:12 by afougere          #+#    #+#             */
/*   Updated: 2016/12/13 13:26:13 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_list	*ft_cp_env_to_sv(t_list **env)
{
	t_list *sv;
	t_list *envp_cp;

	envp_cp = NULL;
	sv = *env;
	while (*env)
	{
		ft_lstadd(&envp_cp, ft_lstnew((*env)->content,
		ft_strlen((*env)->content) + 1));
		(*env) = (*env)->next;
	}
	ft_list_reverse(&envp_cp);
	*env = sv;
	return (envp_cp);
}
