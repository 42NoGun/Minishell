/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:49:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/18 11:52:57 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	free(token->value);
	free(token);
}

void	free_list(t_list *list)
{
	t_node	*temp;

	while (list->len)
	{
		temp = list->head;
		free_token((t_token *) temp->content);
		pop_front(list);
	}
	free(list);
}

void	free_field(t_tree_node *tree_node)
{
	free(tree_node->content);
	free(tree_node);
}

void	free_tree(t_tree *tree)
{
	postorder_traverse(tree->root, free_field);
	free(tree);
}
