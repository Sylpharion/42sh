/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backquotes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <ggobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 09:29:20 by ggobin            #+#    #+#             */
/*   Updated: 2017/01/24 14:44:54 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKQUOTES_H
# define BACKQUOTES_H

typedef struct	s_replace_string
{
	char		*begin;
	char		*res;
	size_t		res_size;
	size_t		i;
	size_t		j;
	size_t		k;
	size_t		l;
}				t_replace_string;

/*
** backquotes.c
*/
char			*ft_exec_back_quotes(char *cmd,
				char const *launched_path);

/*
** backquotes_tools.c
*/
void			*ft_remove_back_quotes(char *str);
void			*ft_quotes_search(char *line);
char			*ft_replace_str_by_str(char *cmd, char *old, char *new);

#endif
