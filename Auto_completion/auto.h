/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelauna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 15:06:02 by mdelauna          #+#    #+#             */
/*   Updated: 2017/02/01 12:51:19 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_H
# define AUTO_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <termcap.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include "../sh.h"

/*
** ft_aff_tab.c
*/
int					ft_aff_all_exec(t_utils *utils);
void				ft_parse_cmd(t_utils *utils);
void				ft_many_or_one(t_utils *utils, t_save *save);

/*
** ft_read_tree.c
*/
void				ft_read_tree(t_tree *tree, t_utils *utils);
void				ft_tree_to_str(t_tree *tree, t_save *save);

/*
** ft_tab_space.c
*/
char				*ft_no_begin_slash(char *pwd, t_utils *utils, int i,
					char *backup);
void				ft_list_cmd_space(t_utils *utils);

/*
** ft_tilde_str.c
*/
char				*ft_tilde_str(char *str, t_save *save);

/*
** ft_utils_auto_comp.c
*/
void				ft_get_path(t_save *save);
void				ft_readdir(t_utils *utils, char *name_open,
					char *name_file);
void				ft_cal_col(t_utils *utils);
void				ft_backup_and_free(t_utils **utils, char *pwd, int i);

/*
** main.c
*/
char				*ft_add_path(char *content, char **path, t_save *save);
void				ft_aff_arg(t_utils *utils, t_save *save, t_termio *termio);
int					ft_tab(t_utils *utils, t_save *save);

#endif
