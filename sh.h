/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 16:51:52 by afougere          #+#    #+#             */
/*   Updated: 2017/02/01 15:04:10 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
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
# include <time.h>

enum					e_env_select {
	NO,
	YES,
};

enum					e_operator {
	NONE,
	OR,
	AND,
};

typedef struct			s_option
{
	int					cd_p;
	int					cd_l;
}						t_option;

typedef struct			s_info_env
{
	char				*pwd;
	char				*oldpwd;
}						t_info_env;

typedef struct			s_setenv
{
	char				*name_var;
	char				*result_var;
}						t_setenv;

typedef struct			s_builts
{
	char				*line;
	t_list				*env;
	t_setenv			*set;
	t_info_env			*info_env;
	t_option			*option;
}						t_builts;

typedef struct			s_glob
{
	char				*fmt;
	int					free_o_n;
}						t_glob;

typedef struct			s_info_col
{
	int					lg_col;
	int					nb_col;
	int					nb_line;
	int					long_word;
}						t_info_col;

typedef struct			s_utils
{
	int					j;
	DIR					*dir;
	t_tree				*tree;
	t_tree				*tmp_tree;
	t_info_col			*info_col;
	t_list				*lst;
	t_list				*lst_read;
	char				*save;
	char				**path;
	int					nb_words;
	t_glob				glob;
	int					aff_or_not;
}						t_utils;

typedef struct			s_termio
{
	pid_t				pid;
	char				buffer[1024];
	int					uppped;
	char				*prompt;
	int					prompt_len;
	int					nb_lines;
	int					cur_line;
	t_list				*history_save;
	char				*copy_for_lst;
	int					size;
	int					i;
	int					yes;
	int					quote;
	int					heredoc;
	char				*name_term;
	char				*save_cut;
	char				*save;
	char				*ctrl_d_heredoc;
	t_list				*history;
	t_list				*cp;
}						t_termio;

typedef struct			s_pipe
{
	int					in;
	int					out;
	int					fd[2];
}						t_pipe;

typedef struct			s_save
{
	int					stdout_dup;
	int					fail_quotes;
	int					semi_i;
	int					fd;
	int					*exit_state;
	int					last_state;
	int					fd_chev;
	char				**env_tmp;
	char				**arg;
	char				**arg_semicolon;
	char				*line;
	char				*name_param;
	char				**arg_param;
	char				*name_file;
	char				**tab_bis;
	char				**stder;
	char				**envp_cp;
	char				*stder_bis;
	char				*sv;
	t_list				*env_cp;
	t_list				*lst_heredoc;
	enum e_operator		last_operator;
	enum e_env_select	use_env_tmp;
	enum e_operator		next_operator;
	t_termio			*termio;
	t_utils				*utils;
	t_builts			*builts;
	t_pipe				*pipe_struct;
	char				*launched_path;
}						t_save;

typedef void			(*t_f)(t_save *);

/*
** execute.c
*/
int						ft_test_acces(char **tab_path, t_save *save,
						char **envc, int i);
void					ft_exec_com(t_save *save, int i);
void					loop(t_save *save, int i);

/*
** fork_pipe.c
*/
int						ft_fork(char **tab, int i, t_save *save);

/*
** ft_aff_term.c
*/
void					ft_aff(t_list *lst, t_save *save, t_termio *termio);
void					ft_replace_curser_prompt(t_termio *termio);
void					ft_clear_cmd(t_termio *termio);
void					ft_replace_curser_and_aff(t_list *lst, t_save *save,
						t_termio *termio);

/*
** ft_check_space.c
*/
void					insert(t_list **lst, char elem, t_termio *termio);
void					ft_check_space_after(t_list **lst, t_save *save,
						t_termio *termio);

/*
** ft_chevron.c
*/
int						ft_init_sv_chev(char **tab, t_save *save, char *str,
						int fd);
int						ft_chevron(t_save *save, char *tab_bis,
						int fd);
/*
** ft_clear_backspace.c
*/
void					ft_clear_cmd_backspace(t_termio *termio);
void					ft_aff_backspace(t_list *lst, t_save *save,
						t_termio *termio);

/*
** ft_cut_copy_paste.c
*/
void					ft_cut_copy_paste(t_save *save, t_termio *termio,
						char buf);

/*
** ft_do_exc.c
*/
int						ft_do_exc(t_save *save, int j, int i);

/*
** ft_double_left_chevron.c
*/
int						ft_double_back_chevron(t_save *save, char **tab_path,
						int fd_bis, char *str);

/*
** ft_error_redirection.c
*/
int						ft_error_redirection(char *str);

/*
** ft_init_save.c
*/
void					ft_useless_function(t_save *save);
void					ft_init_for_quotes(t_termio *termio, t_save *save,
						char ***s_space);
void					ft_init_save(t_save **save, char **argv);
void					ft_parse_arg(t_save **save);
char					**ft_envc(t_save *save);

/*
** ft_init_termcaps.c
*/
int						ft_term(t_save *save, t_termio *term);
void					ft_init_var_save(t_save **save);

/*
** ft_left_chevron.c
*/
int						ft_back_chevron(t_save *save, char *str, int fd_bis);

/*
** ft_list_term.c
*/
int						insert_elem(t_list **lst, char elem, t_save *save,
						t_termio *termio);
void					remove_elem(t_list **lst);
void					ft_str_to_lst(t_list **lst, char *content, t_save *save,
						t_termio *termio);

/*
** ft_message_error.c
*/
int						ft_invalid_command(char **tab);
int						ft_ambigous_input(char **tab);
int						ft_ambigous_output(char **tab);
int						ft_missing_name(char **tab);
int						ft_syntax_error(char **tab);

/*
** ft_message_error_bis.c
*/
int						ft_error_pipe_chev(char **tab, int i);

/*
** ft_nav_history.c
*/
void					ft_history(t_termio *termio, t_save *save, char buf,
						t_list *lst);

/*
** ft_pipe.c
*/
int						ft_pipe_bis(t_save *save, char **tab, int j,
						int fd_bis);
int						ft_pipe(t_save *save, char **tab, char **tab_path,
						int j);
int						ft_split_pipe(t_save *save, int j, char **tab_path);
int						ft_open_chev(t_save *save, int j);

/*
** ft_prompt.c
*/
char					*ft_prompt(void);

/*
** ft_quotes.c
*/
void					ft_parse_quotes_and_exec(t_save *save,
						t_termio *termio);
void					ft_change_env_save(t_save *save, char **envp);

/*
** ft_redir_of_builtins.c
*/
int						ft_search_redir(t_save *save, int i, int nb, char *str);
int						ft_redir_and_bultins(t_save *save, int nb);

/*
** ft_right_chevron.c
*/
int						ft_chevron_right(char **tab_path, char **tab,
						t_save *save, int j);

/*
** ft_signal.c
*/
t_save					*singleton(void);
void					sign(int sig);
int						ft_ctrl_d(char buffer[1024], t_termio *termio,
						t_save *save);
int						ft_jj(int i);

/*
** ft_stderr.c
*/
void					ft_stderr(t_save *save, char *redir);
char					*ft_split_stderr(char **tab, t_save *save, int i);

/*
** ft_term.c
*/
void					ft_lst_to_str(t_list *list, t_save *save,
						t_termio *termio);
void					ft_home_end(t_list **lst, t_termio *termio, char buf);
void					ft_enter_and_glob(t_save *save, t_termio *termio,
						char *cp);
int						ft_puts_goto(t_termio *termio, t_save *save);

/*
** ft_term_bis.c
*/
void					ft_dl_line(t_list **list, t_save *save,
						t_termio *termio);
void					ft_multi_line(t_termio *termio, int buf,
						struct winsize ws);
void					ft_left_right(t_termio *termio, int buf,
						struct winsize ws);

/*
** ft_term_enter.c
*/
int						ft_return(t_termio *termio, t_list *sv);
void					ft_put_buffer(char buffer[1024], t_termio *termio,
						t_save *save);
void					ft_word_cut_copy_term(char buffer[1024],
						t_termio *termio, t_save *save);
int						outc(int c);

/*
** ft_utils.c
*/
void					ft_replace_car(char *str, char c, char b);
t_list					*ft_cp_envp(char **envp);
char					**ft_cp_env_to_tab(t_list *env);

/*
** ft_utils_3.c
*/
void					ft_change_dollar(char ***tab, t_list **env);
void					ft_change_tilde(char ***tab, t_list *env);
char					*ft_fill_for_chev(t_save *save, t_list *lst);

/*
** ft_utils_bis.c
*/
t_list					*ft_cp_env_to_sv(t_list **env);

/*
** ft_utils_heredoc.c
*/
void					ft_add_name_heredoc(char *str, t_save *save);
void					ft_init_name_param(t_save *save, char **tab, int j,
						char **tab_path);

/*
** ft_utils_redirection.c
*/
int						ft_back_double_back(char **tab, char *tab_bis,
						t_save *save, int fd);
int						ft_bultins_or_exec(char **tab, int j, t_save *save,
						int fd);
char					**ft_init_arg_chev(char **tab);
char					*ft_init_name_fd(t_save *save);

/*
** ft_utils_term.c
*/
void					ft_all_list_to_str(t_termio *termio);
void					ft_part_list_to_str(t_termio *termio, int i,
						t_save *save);
void					ft_save_line_to_lst(t_termio *termio, t_save *save);
void					ft_save_history(t_termio *termio, t_save *save,
						char buffer[1024]);

/*
** ft_which_term.c
*/
int						ft_puts_goto_bis(char buffer[1024], t_termio *termio,
						t_list *sv, t_save *save);

/*
** ft_word_by_word_left.c
*/
void					ft_word(char buffer, t_termio *termio);

/*
** ft_word_by_word_right.c
*/
void					ft_word_right(t_termio *termio);

/*
** func_tab.c
*/
void					ft_exit(t_save *save);
int						check_func(t_save *save);
void					ft_change_shlvl(t_save *save);
void					init_glob(char **end, char **cp, t_save *save);

#endif
