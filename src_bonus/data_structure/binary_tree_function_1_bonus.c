/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_fuinction_1_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:09:09 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/23 17:13:20 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "minishell_bonus.h"
#include "binary_tree_bonus.h"
#include "libft.h"

t_tree	*init_tree(void)
{
	t_tree	*tree;

	tree = _malloc(sizeof(t_tree));
	tree->root = NULL;
	return (tree);
}

t_tree_node	*make_tree_node(void *content)
{
	t_tree_node	*new_node;

	new_node = _malloc(sizeof(t_tree_node));
	new_node->content = content;
	new_node->level = 0;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	push_left(t_tree_node *parent, t_tree_node *child, t_tree *tree)
{
	if (tree->root == NULL)
	{
		tree->root = child;
		tree->root->level = 1;
		return ;
	}
	parent->left = child;
	child->level = parent->level + 1;
}

void	push_right(t_tree_node *parent, t_tree_node *child, t_tree *tree)
{
	if (tree->root == NULL)
	{
		tree->root = child;
		tree->root->level = 1;
		return ;
	}
	parent->right = child;
	child->level = parent->level + 1;
}

void	push_right_endpoint(t_tree_node *parent, t_tree_node *child,
			t_tree *tree)
{
	while (parent->right)
		parent = parent->right;
	push_right(parent, child, tree);
}
