/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:20:21 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/25 21:03:12 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static t_field	*make_field(t_node **cur_node)
{
	t_token	*token;
	t_field	*field;

	field = _malloc(sizeof(t_field));
	token = (*cur_node)->content;
	field->start_ptr = *cur_node;
	field->len = 0;
	if (token->priority == 2)
	{
		while (*cur_node && token->priority == 2)
		{
			++field->len;
			*cur_node = (*cur_node)->next;
			if (*cur_node)
				token = (*cur_node)->content;
		}
	}
	else
	{
		++field->len;
		*cur_node = (*cur_node)->next;
	}
	return (field);
}

static void	hang_from_tree(t_tree *cmd_tree, t_field *field)
{
	int			cur_priority;
	int			root_priority;
	t_tree_node	*cur_tree_node;

	cur_priority = ((t_token *)(field->start_ptr->content))->priority;
	root_priority = ((t_token *)(cmd_tree->root->content))->priority;
	cur_tree_node = make_tree_node(field);
	if (root_priority >= cur_priority)
	{
		push_left(cur_tree_node, cmd_tree->root, cmd_tree);
		cmd_tree->root = cur_tree_node;
	}
	if (root_priority < cur_priority)
	{
		if (cur_priority != 2)
		{
			push_left(cur_tree_node, cmd_tree->root->right, cmd_tree);
			push_right(cmd_tree->root->right, cur_tree_node, cmd_tree);
		}
		else
			push_right_endpoint(cmd_tree->root, cur_tree_node, cmd_tree);
	}
}

t_tree	*make_tree(t_list *cmd_list)
{
	t_tree		*cmd_tree;
	t_field		*field;
	t_node		*cur_node;

	cmd_tree = init_tree();
	cur_node = cmd_list->head;
	field = make_field(&cur_node);
	push_left(NULL, make_tree_node(field), cmd_tree);
	while (cur_node)
	{
		field = make_field(&cur_node);
		hang_from_tree(cmd_tree, field);
	}
	return (cmd_tree);
}

bool	can_parse(t_list **tokenized_list, t_tree **cmd_tree,
	t_list **cmd_list, char *line)
{
	*tokenized_list = tokenize(line);
	*cmd_tree = make_tree(*tokenized_list);
	free(line);
	if (!is_valid_operator_or_redirection(*cmd_tree))
	{
		free_list_node_token(*tokenized_list);
		free_tree_node_field(*cmd_tree);
		return (false);
	}
	*cmd_list = convert_tree_to_exec_list(*cmd_tree);
	if (!is_valid_bracket_subshell(*cmd_list))
	{
		free_list_node_token(*tokenized_list);
		free_tree_node_field(*cmd_tree);
		free_list_only_node(*cmd_list);
		return (false);
	}
	return (true);
}
