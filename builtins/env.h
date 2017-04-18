/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <ggobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 13:33:13 by ggobin            #+#    #+#             */
/*   Updated: 2017/02/06 13:59:48 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../libft/libft.h"
# include "../sh.h"
# include <unistd.h>
# include <stdio.h>

typedef struct		s_envcpy
{
	char			**env_cpy;
	char			**arg_cpy;
	char			**path;
	int				i;
}					t_envcpy;

typedef struct		s_update {
	char			*equals[2];
	char			c[2];
	int				i;
}					t_update;

/*
** env.c
*/
void				ft_var(t_envcpy *e, t_save *save);
void				ft_env(t_save *save);

/*
** env_bis.c
*/
void				ft_printenv(char **env, t_save *save);
int					ft_tablen(char **tab);
int					ft_keycmp(char *str, char *key);
void				ft_exec_env(t_envcpy *e, t_save *save);
void				ft_get_env_lst(char **envp, t_builts *builts);

/*
** ft_cd.c
*/
void				ft_change_old_pwd(t_builts *builts, char *for_chdir,
					char *pwd_link, t_list *lst);
void				ft_cd(t_save *save);

/*
** ft_echo.c
*/
void				ft_echo(t_save *save);

/*
** ft_error_cd.c
*/
void				ft_no_file(t_save *save, char *str);
int					ft_error_home(t_builts *builts, char *str);
void				ft_change_var(t_list *lst, char *tmp_link,
					char *tmp_link_pwd, t_list *tmp);

/*
** ft_options.c
*/
int					ft_check_option(t_save *save);
t_list				*ft_check_option_cd(t_builts *builts, t_save *save);

/*
** ft_setenv.c
*/
void				ft_parse_line_setenv(t_builts *builts, char *str);
void				ft_create_name_var(t_builts *builts, char *var);
void				ft_setenv(t_save *save);

/*
** ft_unsetenv.c
*/
void				ft_unsetenv(t_save *save);

/*
** ft_utils_builtins.c
*/
char				*ft_getenv(char *str, t_list *lst);
void				ft_change_env(t_list *lst, char *str);
void				ft_get_info_env(t_builts *builts);
void				ft_pwd(t_builts *builts);
t_list				*ft_create_env(t_list *lst);

/*
** ft_utils_cd.c
*/
int					ft_check_cd(t_save *save, t_list *lst, int i);
void				ft_change_prompt(char *tmp, t_save *save, t_list **lst);

/*
** option.c
*/
void				ft_opt_error(int error, char c);
void				ft_opt_i(char ***env);
int					ft_opt_u(t_envcpy *e, char *arg);
int					ft_opt(char *opt, int i);

/*
** other.c
*/
void				ft_env_usage();

/*
** set_env.c
*/
char				**ft_env_set(t_envcpy *e, char *str);
void				change_env_shlvl(t_list **env, char *str);
char				*ft_init_ft_setenv(t_save *save);

/*
** unset_env.c
*/
int					ft_verif_env(char **env, char *str);
char				**ft_env_unset(char **env, char *str);
int					ft_unset(t_envcpy *e, t_save *save);

/*
** utils_env.c
*/
char				*ft_getpath(char **env);
int					ft_free_env(t_envcpy *e);
void				ft_init_env(t_envcpy *e, char **env, t_save *save);
void				ft_parse_path(t_envcpy *e, t_save *save);

#endif
