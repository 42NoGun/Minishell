/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_function_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:11:26 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/10/26 09:09:46 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_list	*make_node(void *content_1, void *content_2)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		terminate("ERROR : MALLOC");
	new_node->content_1 = content_1;
	new_node->content_2 = content_2;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	pop_front(t_list_info *list_info)
{
	t_list	*cursor;

	cursor = list_info->head;
	list_info->head = cursor->next;
	if (list_info->head == NULL)
		list_info->tail = NULL;
	else
		list_info->head->prev = NULL;
	list_info->len--;
	free(cursor);
}

void	pop_back(t_list_info *list_info)
{
	t_list	*cursor;

	cursor = list_info->tail;
	list_info->tail = cursor->prev;
	if (list_info->tail == NULL)
		list_info->head = NULL;
	else
		list_info->tail->next = NULL;
	list_info->len--;
	free(cursor);
}

void	push_front(t_list_info *list_info, t_list *node)
{
	node->next = list_info->head;
	node->prev = NULL;
	if (list_info->head == NULL)
	{
		list_info->head = node;
		list_info->tail = node;
	}
	else
	{
		list_info->head->prev = node;
		list_info->head = node;
	}
	list_info->len++;
}

void	push_back(t_list_info *list_info, t_list *node)
{
	node->next = NULL;
	node->prev = list_info->tail;
	if (list_info->head == NULL)
	{
		list_info->head = node;
		list_info->tail = node;
	}
	else
	{
		list_info->tail->next = node;
		list_info->tail = node;
	}
	list_info->len++;
}
