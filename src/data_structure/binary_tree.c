/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:09:09 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/03 11:59:45 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"
#include "libft.h"

t_tree	*init_tree(void)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		ft_terminate(NULL, errno);
	tree->root = NULL;
	return (tree);
}

t_tree_node	*make_tree_node(void *content)
{
	t_tree_node	*new_node;

	new_node = malloc(sizeof(t_tree_node));
	if (!new_node)
		terminate(NULL, errno);
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

// void	inorder_traverse(t_tree *tree, t_tree_node *cursor)
// {
// 	if (cursor->left == NULL)
// 		return ;

// 	inorder_traverse(tree, cursor->left);
// 	pipex(tree->content);
// 	inorder_traverse(tree, cursor->right);
// }