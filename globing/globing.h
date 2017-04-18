/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:33:59 by ggobin            #+#    #+#             */
/*   Updated: 2017/01/23 18:13:00 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBING_H
# define GLOBING_H

# include "../libft/libft.h"
# include "../Auto_completion/auto.h"

typedef struct		s_glob_data
{
	char			**tmp;
	char			**s_combos;
	char			*to_free;
	size_t			i;
}					t_glob_data;

typedef struct		s_all
{
	char			*end;
	char			*all_chars;
	size_t			i;
	char			*after;
	char			*to_add;
	char			*tmp;
	char			*new;
}					t_all;

/*
** globing.c
*/
char				*all(char *before, char *str);
int					check_pattern(char *pattern);
int					ft_glob(t_glob g, char *name);

/*
** globing_bis.c
*/
char				*from_to(char *before, char *str);
char				*generate_combos(char *str);

#endif
