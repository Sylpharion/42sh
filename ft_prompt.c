/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:06:11 by smassand          #+#    #+#             */
/*   Updated: 2017/01/03 12:54:15 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_prompt(void)
{
	char *pwd;
	char *prompt;

	prompt = NULL;
	pwd = getcwd(NULL, 0);
	prompt =
	ft_strdup("\033[0;31m[JACKY\033[0;34m & \033[0;33mMINISHELL] \033[0;32m");
	if (pwd)
		prompt = ft_strjoin_free(prompt, pwd, 3);
	prompt = ft_strjoin_free(prompt, "\033[0;32m ➤ \033[0m", 1);
	return (prompt);
}
