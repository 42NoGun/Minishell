/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_function_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:11:26 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/04 15:22:12 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "libft.h"

t_node	*make_node(void *content)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		ft_terminate(NULL);
	new_node->content = content;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	pop_front(t_list *list)
{
	t_node	*cursor;

	if (list->len == 0)
		return ;
	cursor = list->head;
	list->head = cursor->next;
	if (list->head == NULL)
		list->tail = NULL;
	else
		list->head->prev = NULL;
	list->len--;
	free(cursor);
}

void	pop_back(t_list *list)
{
	t_node	*cursor;

	if (list->len == 0)
		return ;
	cursor = list->tail;
	list->tail = cursor->prev;
	if (list->tail == NULL)
		list->head = NULL;
	else
		list->tail->next = NULL;
	list->len--;
	free(cursor);
}

void	push_front(t_list *list, t_node *node)
{
	node->next = list->head;
	node->prev = NULL;
	if (list->head == NULL)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->head->prev = node;
		list->head = node;
	}
	list->len++;
}

void	push_back(t_list *list, t_node *node)
{
	node->next = NULL;
	node->prev = list->tail;
	if (list->head == NULL)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	list->len++;
}
