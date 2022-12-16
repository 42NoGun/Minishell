/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:49:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/16 16:54:52 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list_only_node(t_list *list)
{
	t_node	*temp;

	while (list->len)
		pop_front(list);
	free(list);
}

void	free_list_node_content(t_list *list)
{
	t_node	*cur_node;
	t_node	*next_node;

	cur_node = list->head;
	while (cur_node)
	{
		next_node = cur_node->next;
		free(cur_node->content);
		free(cur_node);
		cur_node = next_node;
	}
	free(list);
}

void	free_token(t_token *token)
{
	free(token->value);
	free(token);
}

void	free_list_node_token(t_list *list)
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

void	free_tree_node_field(t_tree *tree)
{
	postorder_traverse(tree->root, free_field);
	free(tree);
}

void	free_2d_str(char **arr_str)
{
	int	i;

	i = 0;
	while (arr_str[i])
	{
		free(arr_str[i]);
		++i;
	}
	// free(arr_str[i]); ㅠㅠ 
	free(arr_str);
}
