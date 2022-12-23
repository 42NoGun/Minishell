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

#include <errno.h>
#include "binary_tree.h"
#include "libft.h"

void	inorder_traverse(t_tree_node *cursor, void (*f)(t_tree_node *))
{
	if (cursor == NULL)
		return ;
	inorder_traverse(cursor->left, f);
	f(cursor);
	inorder_traverse(cursor->right, f);
}

void	inorder_traverse_make_exec_list(t_tree_node *cursor, t_list *exec_list,
	void (*f)(t_list *, t_tree_node *))
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

	b = false;
	if (cursor == NULL)
		return (b);
	b |= inorder_traverse_bool(cursor->left, f);
	b |= f(cursor);
	b |= inorder_traverse_bool(cursor->right, f);
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
