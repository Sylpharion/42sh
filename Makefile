# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afougere <afougere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/21 11:52:24 by afougere          #+#    #+#              #
#    Updated: 2017/02/05 08:45:03 by ggobin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re all

NAME = 42sh

SRC = mini.c ft_utils.c builtins/ft_setenv.c builtins/ft_unsetenv.c \
func_tab.c  ft_utils_bis.c  builtins/ft_echo.c builtins/ft_cd.c \
ft_utils_3.c ft_double_left_chevron.c builtins/ft_error_cd.c \
ft_pipe.c ft_error_redirection.c ft_term.c ft_utils_term.c \
ft_term_bis.c ft_cut_copy_paste.c ft_message_error.c \
ft_term_enter.c ft_quotes.c ft_utils_redirection.c \
ft_aff_term.c ft_list_term.c ft_word_by_word_left.c \
ft_word_by_word_right.c ft_redir_of_bultins.c  \
ft_signal.c ft_stderr.c ft_right_chevron.c \
ft_left_chevron.c ft_message_error_bis.c operators.c \
ft_init_save.c ft_logic_operator.c ft_check_space.c \
Auto_completion/ft_aff_tab.c builtins/ft_options.c \
Auto_completion/ft_tab_space.c Auto_completion/ft_read_tree.c \
globing/globing.c globing/queries.c builtins/ft_utils_builtins.c \
globing/is_matching.c globing/globing_bis.c Auto_completion/main.c \
ft_init_termcaps.c Auto_completion/ft_tilde_str.c \
Auto_completion/ft_utils_auto_comp.c \
builtins/env.c   builtins/set_env.c  builtins/unset_env.c  builtins/other.c \
builtins/option.c builtins/utils_env.c ft_do_exc.c \
builtins/env_bis.c ft_nav_history.c ft_prompt.c ft_clear_backspace.c \
ft_utils_heredoc.c ft_which_term.c ft_chevron.c builtins/ft_utils_cd.c \
backquotes/backquotes.c backquotes/backquotes_tools.c execute.c fork_pipe.c \
quotes_tools.c init_glob.c builtins/ft_cd_bis.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@clang $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a -ltermcap

%.o:%.c
	clang $(FLAGS) -o $@ -c $<

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C libft/ fclean
	@rm -rf $(NAME)

re: fclean all
