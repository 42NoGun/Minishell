/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:36:52 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/10/20 13:42:21 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;	
	void			*content_1;
	void			*content_2;
}	t_list;

typedef struct s_list_info
{
	struct s_list	*head;
	struct s_list	*tail;
	int				len;
	int				flag;
}	t_list_info;

t_list	*make_node(void *content_1, void *content_2);
void	pop_front(t_list_info *list_info);
void	pop_back(t_list_info *list_info);
void	push_front(t_list_info *list_info, t_list *node);
void	push_back(t_list_info *list_info, t_list *node);
void	clear_list(t_list_info *list_info);
void	swap_node(t_list_info *list_info);
void	init_list(t_list_info *list_info, int flag);

#endif