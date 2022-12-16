/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:36:52 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/16 13:07:11 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;	
	void			*content;
}	t_node;

typedef struct s_list
{
	struct s_node	*head;
	struct s_node	*tail;
	int				len;
}	t_list;

t_node	*make_node(void *content);
void	pop_front(t_list *list);
void	pop_middle(t_list *list, t_node *node);
void	pop_back(t_list *list);
void	push_front(t_list *list, t_node *node);
void	push_back(t_list *list, t_node *node);
void	clear_list(t_list *list);
void	swap_node(t_list *list);
t_list	*init_list(void);

#endif