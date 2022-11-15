/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:40:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/15 17:05:29 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_operator_node_has_child(t_tree_node *cursor)
{
	t_token	*token;

	token = (t_token *)((t_field *)(cursor->content))->start_ptr->content;
	if (token->priority == 0 || token->priority == 1)
	{
		if (cursor->left == NULL || cursor->right == NULL)
			return (false);
	}
	return (true);
}

bool	check_syntax_error(t_tree *cmd_tree)
{
	if (inorder_traverse_bool(cmd_tree->root,
			check_operator_node_has_child) == false)
	{
		ft_putstr_fd("minishell : syntax error\n", 2);
		return (false);
	}
	return (true);
}
