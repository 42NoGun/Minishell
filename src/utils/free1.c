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

