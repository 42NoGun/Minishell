/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:09:09 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/01 11:32:21 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"
#include "libft.h"
#include <errno.h>

t_tree	*init_tree(void)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		ft_terminate("init_tree, malloc error");
	tree->root = NULL;
	return (tree);
}

t_tree_node	*make_tree_node(void *content)
{
	t_tree_node	*new_node;

	new_node = malloc(sizeof(t_tree_node));
	if (!new_node)
		ft_terminate("make_tree_node, malloc error");
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

void	inorder_traverse(t_tree_node *cursor, void (*f)(t_tree_node *))
{
	if (cursor == NULL)
		return ;
	inorder_traverse(cursor->left, f);
	f(cursor);
	inorder_traverse(cursor->right, f);
}

void	inorder_traverse_make_exec_list(t_tree_node *cursor, t_list *exec_list, void (*f)(t_list *, t_tree_node *))
{
	if (cursor == NULL)
		return ;
	inorder_traverse_make_exec_list(cursor->left, exec_list, f);
	f(exec_list, cursor);
	inorder_traverse_make_exec_list(cursor->right, exec_list, f);
}

bool	inorder_traverse_bool(t_tree_node *cursor, bool (*f)(t_tree_node *))
{
	bool	b;

	b = true;
	if (cursor == NULL)
		return (b);
	b &= inorder_traverse_bool(cursor->left, f);
	b &= f(cursor);
	b &= inorder_traverse_bool(cursor->right, f);
	return (b);
}

void	postorder_traverse(t_tree_node *cursor, void (*f)(t_tree_node *))
{
	if (cursor == NULL)
		return ;
	postorder_traverse(cursor->left, f);
	postorder_traverse(cursor->right, f);
	f(cursor);
}
