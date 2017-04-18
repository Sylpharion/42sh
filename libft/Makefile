# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afougere <afougere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/27 14:57:22 by afougere          #+#    #+#              #
#    Updated: 2016/08/24 13:15:46 by afougere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_lstdel.c ft_memcpy.c ft_putnbr_fd.c ft_strdup.c \
ft_strncmp.c ft_strsub.c ft_bzero.c ft_lstdelone.c ft_memdel.c ft_putstr.c \
ft_striter.c ft_strncpy.c ft_strtrim.c ft_isalnum.c ft_lstiter.c ft_memmove.c \
ft_putstr_fd.c ft_striteri.c ft_strnequ.c ft_tolower.c ft_isalpha.c \
ft_lstmap.c ft_memset.c ft_strcat.c ft_strjoin.c ft_strnew.c ft_toupper.c \
ft_isascii.c ft_lstnew.c ft_putchar.c ft_strchr.c ft_strlcat.c ft_strnstr.c \
ft_isdigit.c ft_memalloc.c ft_putchar_fd.c ft_strclr.c ft_strlen.c ft_strequ.c\
 ft_isprint.c ft_memccpy.c ft_putendl.c ft_strcmp.c ft_strmap.c \
ft_strrchr.c ft_itoa.c ft_memchr.c ft_putendl_fd.c ft_strcpy.c ft_strmapi.c \
ft_strsplit.c ft_lstadd.c ft_memcmp.c ft_putnbr.c ft_strdel.c ft_strncat.c \
ft_strstr.c ft_strjoin_free.c ft_pow.c ft_sqrt.c ft_list_size.c ft_list_swap.c \
ft_list_sort.c ft_list_reverse.c get_next_line.c ft_list_remove_if.c \
ft_free_tab.c ft_list_del.c ft_free_list.c ft_list_size_by_prev.c \
ft_sort_tab.c ft_free_tree.c ft_add_node.c ft_create_node.c

O = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
		@clang -c -Wall -Wextra -Werror $(SRC)
		@ar rc $(NAME) $(O)

.PHONY : clean flcean re all

clean:
		@rm -f $(O)

fclean: clean
		@rm -f $(NAME)

re: fclean all
