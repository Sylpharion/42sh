/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 11:49:14 by afougere          #+#    #+#             */
/*   Updated: 2016/11/02 11:49:15 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tree(t_tree **tree)
{
	if (!*tree)
		return ;
	ft_free_tree(&(*tree)->left);
	ft_free_tree(&(*tree)->right);
	free((*tree)->content);
	free(*tree);
	*tree = NULL;
}
