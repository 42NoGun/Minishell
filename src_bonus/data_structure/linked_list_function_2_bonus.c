/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_function_2_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 14:53:59 by jiyun             #+#    #+#             */
/*   Updated: 2022/12/23 17:13:46 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_bonus.h"
#include "libft.h"

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

void	pop_middle(t_list *list, t_node *node)
{
	t_node	*cursor;

	cursor = node;
	cursor->prev->next = cursor->next;
	cursor->next->prev = cursor->prev;
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
