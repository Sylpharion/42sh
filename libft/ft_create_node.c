/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 11:47:34 by afougere          #+#    #+#             */
/*   Updated: 2016/11/02 11:47:36 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_create_node(void *content)
{
	t_tree *new;

	new = (t_tree *)malloc(sizeof(t_tree));
	new->content = ft_strdup((char *)content);
	new->left = NULL;
	new->right = NULL;
	return (new);
}
