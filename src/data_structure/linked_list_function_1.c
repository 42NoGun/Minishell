/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_function_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:11:26 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/16 13:17:49 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "libft.h"

t_list	*init_list(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		ft_terminate("init_list, malloc error");
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
	return (list);
}

t_node	*make_node(void *content)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		ft_terminate("make_node, malloc error");
	new_node->content = content;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	swap_node(t_list *list)
{
	t_node	*fixed_node;
	t_node	*cursor;
	t_node	*cursor_l;

	cursor = list->tail;
	cursor_l = cursor->prev;
	fixed_node = cursor_l->prev;
	cursor->prev = fixed_node;
	if (fixed_node != NULL)
		fixed_node->next = cursor;
	cursor->next = cursor_l;
	cursor_l->prev = cursor;
	cursor_l->next = NULL;
	if (cursor_l == list->head)
		list->head = cursor;
	list->tail = cursor_l;
}
