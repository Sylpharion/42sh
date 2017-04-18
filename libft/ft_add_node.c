/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 11:47:20 by afougere          #+#    #+#             */
/*   Updated: 2016/11/02 11:47:21 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_node(void *content, t_tree **tree,
int (*cmpf)(const char *, const char*))
{
	if (*tree == NULL)
		*tree = ft_create_node(content);
	else if ((*cmpf)(content, (*tree)->content) < 0)
		ft_add_node(content, &(*tree)->left, cmpf);
	else
		ft_add_node(content, &(*tree)->right, cmpf);
}
