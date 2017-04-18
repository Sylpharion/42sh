/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:11:16 by afougere          #+#    #+#             */
/*   Updated: 2017/02/05 09:48:20 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

typedef struct	s_cd
{
	char		*cwd_cmpl[2];
	char		*args;
	t_list		*pwds[2];
	char		*str_tmp;
	char		*next_dir;
}				t_cd;

int				check_file_stats(t_cd *cd, char flag);
void			check_parameters(t_cd *cd, t_save *save);
int				simple_chdir(char *args, t_cd *cd, char flag);
void			chdir_and_update_env(t_save *save, char **cwd_cmpl,
				t_list **pwds, char const *env_var);

#endif
