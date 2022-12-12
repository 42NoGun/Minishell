/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:40:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/12 14:52:03 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redirection(t_token *token)
{
	if (ft_strcmp(token->value, "<<") == 0)
	{
		return (true);
	}
	if (ft_strcmp(token->value, ">>") == 0)
	{
		return (true);
	}
	if (ft_strcmp(token->value, ">") == 0)
	{
		return (true);
	}
	if (ft_strcmp(token->value, "<") == 0)
	{
		return (true);
	}
	return (false);
}

static bool	check_redirection_error(t_field *field)
{
	t_token	*token;
	t_node	*node;
	int		len;

	len = field->len;
	node = (t_node *)field->start_ptr;
	while (len > 0)
	{
		token = node->content;
		if (is_redirection(token))
		{
			if (len == 1)
				return (false);
			if (is_redirection(node->next->content))
				return (false);
		}
		node = node->next;
		--len;
	}
	return (true);
}

static bool	check_operator_node_has_child_and_redirection(t_tree_node *cursor)
{
	t_field	*field;
	t_token	*token;

	field = (t_field *)cursor->content;
	token = (t_token *)field->start_ptr->content;
	if (token->priority == 0 || token->priority == 1)
	{
		if (cursor->left == NULL || cursor->right == NULL)
			return (false);
	}
	// redirection(<, <<, >, >>) 기호가 있으면 ("쿼트 안에 있는 건 아님")
	// 그 다음 토큰이 redirection 기호거나 마지막이면  syntax error  
	if (check_redirection_error(field) == false)
		return (false);
	return (true);
}

bool	check_syntax_error(t_tree *cmd_tree)
{
	if (inorder_traverse_bool(cmd_tree->root,
			check_operator_node_has_child_and_redirection) == false)
	{
		ft_putstr_fd("minishell : syntax error\n", 2);
		g_exit_status = 2 << 8;
		return (false);
	}
	return (true);
}
