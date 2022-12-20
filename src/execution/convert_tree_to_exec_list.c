/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tree_to_exec_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:42:57 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/20 11:29:20 by hanbkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	make_execution_order_list(t_list *list, t_tree_node *node)
{
	t_field	*field;

	field = (t_field *)node->content;
	push_back(list, make_node(field));
}

t_list	*convert_tree_to_exec_list(t_tree *cmd_tree)
{
	t_list	*exec_list;

	exec_list = init_list();
	inorder_traverse_make_exec_list(
		cmd_tree->root, exec_list, make_execution_order_list);
	return (exec_list);
}
