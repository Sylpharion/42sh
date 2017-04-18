/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_save.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 13:53:23 by afougere          #+#    #+#             */
/*   Updated: 2017/02/05 08:25:16 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_useless_function(t_save *save)
{
	if (save->termio->quote == 1)
		exit(0);
	ft_putstr(save->termio->prompt);
}

void	ft_init_for_quotes(t_termio *termio, t_save *save, char ***s_space)
{
	termio->save = NULL;
	*s_space = NULL;
	termio->save = ft_strdup(save->line);
}

void	ft_init_save(t_save **save, char **argv)
{
	*save = singleton();
	(*save)->termio = (t_termio *)malloc(sizeof(t_termio));
	(*save)->termio->history = NULL;
	(*save)->termio->cp = NULL;
	(*save)->exit_state = (int *)malloc(sizeof(int));
	(*save)->line = NULL;
	(*save)->utils = (t_utils *)malloc(sizeof(t_utils));
	(*save)->utils->info_col = (t_info_col *)malloc(sizeof(t_info_col));
	(*save)->builts = (t_builts *)malloc(sizeof(t_builts));
	(*save)->builts->info_env = (t_info_env *)malloc(sizeof(t_info_env));
	(*save)->builts->info_env->pwd = NULL;
	(*save)->builts->info_env->oldpwd = NULL;
	(*save)->builts->option = (t_option *)malloc(sizeof(t_builts));
	(*save)->builts->option->cd_p = 0;
	(*save)->builts->option->cd_l = 0;
	(*save)->last_state = 0;
	(*save)->termio->prompt = NULL;
	(*save)->utils->path = NULL;
	(*save)->termio->prompt = ft_prompt();
	(*save)->termio->prompt_len = ft_strlen((*save)->termio->prompt) - 41;
	(*save)->utils->path = NULL;
	(*save)->stder = NULL;
	(*save)->stder_bis = NULL;
	(*save)->sv = NULL;
	(*save)->launched_path = ft_strjoin_free(getcwd(NULL, 0), &argv[0][1], 1);
}

void	ft_parse_arg(t_save **save)
{
	char *cp;

	ft_jj(1);
	ft_replace_car((*save)->line, '\t', ' ');
	cp = ft_strdup((*save)->line);
	free((*save)->line);
	(*save)->line = ft_strtrim(cp);
	free(cp);
	(*save)->arg_semicolon = ft_strsplit((*save)->line, ';');
}

char	**ft_envc(t_save *save)
{
	char **envc;

	if (save->use_env_tmp == NO)
		envc = ft_cp_env_to_tab(save->builts->env);
	else
	{
		envc = save->env_tmp;
		save->use_env_tmp = NO;
	}
	return (envc);
}
