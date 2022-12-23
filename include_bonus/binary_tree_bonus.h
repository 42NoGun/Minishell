/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:34:07 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/23 17:08:30 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_BONUS_H
# define BINARY_TREE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "linked_list_bonus.h"

typedef struct s_tree_node	t_tree_node;
typedef struct s_tree		t_tree;

typedef struct s_tree_node
{
	t_tree_node	*left;
	t_tree_node	*right;
	void		*content;
	int			level;
}	t_tree_node;

typedef struct s_tree
{
	t_tree_node	*root;
}	t_tree;

t_tree		*init_tree(void);
t_tree_node	*make_tree_node(void *content);
void		push_left(t_tree_node *parent, t_tree_node *child, t_tree *tree);
void		push_right(t_tree_node *parent, t_tree_node *child, t_tree *tree);
void		push_right_endpoint(t_tree_node *parent, t_tree_node *child,
				t_tree *tree);
void		inorder_traverse(t_tree_node *cursor, void (*f)(t_tree_node *));
bool		inorder_traverse_bool(t_tree_node *cursor,
				bool (*f)(t_tree_node *));
void		postorder_traverse(t_tree_node *cursor, void (*f)(t_tree_node *));
void		inorder_traverse_make_exec_list(t_tree_node *cursor,
				t_list *exec_list, void (*f)(t_list *, t_tree_node *));

#endif
