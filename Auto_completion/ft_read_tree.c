/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 11:55:34 by afougere          #+#    #+#             */
/*   Updated: 2017/02/02 17:07:04 by mdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

void	ft_read_tree(t_tree *tree, t_utils *utils)
{
	int			size;

	ft_cal_col(utils);
	if (!tree)
	{
		utils->j = 0;
		return ;
	}
	if (tree->left)
		ft_read_tree(tree->left, utils);
	if (utils->j == utils->info_col->nb_col)
	{
		write(1, "\n", 1);
		utils->j = 0;
	}
	utils->j++;
	ft_putstr(tree->content);
	size = ft_strlen(tree->content);
	while (size < utils->info_col->long_word + 1)
	{
		write(1, " ", 1);
		size++;
	}
	if (tree->right)
		ft_read_tree(tree->right, utils);
}

void	ft_tree_to_str(t_tree *tree, t_save *save)
{
	char *tmp;

	if (!tree)
		return ;
	if (tree->left)
		ft_tree_to_str(tree->left, save);
	tmp = ft_strdup(tree->content);
	free(tree->content);
	tree->content = ft_add_path(tmp, save->utils->path, save);
	free(tmp);
	save->line = ft_strjoin_free(save->line, " ", 1);
	save->line = ft_strjoin_free(save->line, tree->content, 1);
	if (tree->right)
		ft_tree_to_str(tree->right, save);
}
