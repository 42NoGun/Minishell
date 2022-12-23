/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:40:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/20 10:54:58 by hanbkim          ###   ########.fr       */
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

static bool	is_redirection_error(t_field *field)
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
				return (true);
			if (is_redirection(node->next->content))
				return (true);
		}
		node = node->next;
		--len;
	}
	return (false);
}

static bool	has_syntax_error(t_tree_node *cursor)
{
	t_field	*field;
	t_token	*token;

	field = (t_field *)cursor->content;
	token = (t_token *)field->start_ptr->content;
	if (token->priority == 0 || token->priority == 1)
	{
		if (cursor->left == NULL || cursor->right == NULL)
			return (true);
	}
	if (is_redirection_error(field) == true)
		return (true);
	return (false);
}

bool	is_valid_operator_or_redirection(t_tree *cmd_tree)
{
	if (inorder_traverse_bool(cmd_tree->root,
			has_syntax_error) == true)
	{
		ft_putstr_fd("minishell : syntax error\n", 2);
		g_exit_status = 2 << 8;
		return (false);
	}
	return (true);
}
