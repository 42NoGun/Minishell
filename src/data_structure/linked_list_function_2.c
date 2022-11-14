/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_function_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 14:53:59 by jiyun             #+#    #+#             */
/*   Updated: 2022/11/14 16:29:25 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "libft.h"

// void	clear_list(t_list *list)
// {
// 	t_node	*temp;

// 	while (list->head != NULL)
// 	{
// 		temp = list->head->next;
// 		free_content();
// 		free(list->head->content);
// 		free(list->head);
// 		list->head = temp;
// 	}
// }

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
