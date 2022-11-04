/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:34:07 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/04 15:17:11 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
# define BINARY_TREE_H
# include <unistd.h>
# include <stdlib.h>

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
#endif
